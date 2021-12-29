/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:08:18 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/29 16:24:41 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_special(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (ft_tolower(s1[i]) != s2[i])
			return (1);
		i++;
	}
	if (s1[i] || s2[i])
		return (1);
	return (0);
}

int	launch_command(t_btree *node, char *cmd)
{
	if (node && cmd != 0)
	{
		if (ft_strequ(cmd, "echo"))
			echo(node->arg);
		else if (ft_strequ(cmd, "env"))
			cmd_env(node->arg);
		else if (ft_strequ(cmd, "pwd"))
			pwd(1);
		else if (ft_strequ(cmd, "cd"))
			cd(node->arg);
		else if (ft_strequ(cmd, "export"))
			export(node->arg);
		else if (ft_strequ(cmd, "unset"))
			unset(node->arg);
		else if (ft_strequ(cmd, "exit"))
			cmd_exit(node->arg);
		else
			fork_execve(node);
	}
	return (0);
}

void	store_pipe_fd(int pipe_fd0, int pipe_fd1)
{
	if (pipe_fd0 != 0 && pipe_fd0 != 1)
		fd_lst_add_back(&g_data.fd_list, pipe_fd0);
	if (pipe_fd1 != 0 && pipe_fd1 != 1)
		fd_lst_add_back(&g_data.fd_list, pipe_fd1);
}

void	launch_pipe(t_btree *node, pid_t pid)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	store_pipe_fd(pipe_fd[0], pipe_fd[1]);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		launch_tree(node->left);
		close(pipe_fd[1]);
		clean_exit(0, 0);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		launch_tree(node->right);
		close(pipe_fd[0]);
		pid = waitpid(0, &g_data.chd_status, 0);
		clean_process();
	}
}

int	launch_tree(t_btree *tree)
{	
	if (tree->left == NULL && tree->right == NULL)
	{
		if (tree->redir != NULL)
		{
			if (launch_redir(tree->redir) == -1)
				return (-1);
		}
		if (tree->arr == NULL
			|| launch_command(tree, tree->arr[0]) == -1)
			return (-1);
		clean_process();
	}
	else if ((tree->left != NULL && tree->left->arr != NULL)
		&& (tree->right != NULL && tree->right->arr != NULL)
		&& ft_strequ(tree->arg->word, "|"))
		launch_pipe(tree, 0);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (0);
}
