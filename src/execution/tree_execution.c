
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
		if (!ft_strcmp_special(cmd, "echo"))
			echo(node->arg);
		else if (!ft_strcmp_special(cmd, "env"))
			cmd_env(node->arg);
		else if (!ft_strcmp_special(cmd, "pwd"))
			pwd(1);
		else if (!ft_strcmp_special(cmd, "cd"))
			cd(node->arg);
		else if (!ft_strcmp_special(cmd, "export"))
			export(node->arg);
		else if (!ft_strcmp_special(cmd, "unset"))
			unset(node->arg);
		else if (!ft_strcmp_special(cmd, "exit"))
			cmd_exit(node->arg);
		else
			fork_execve(node);
	}
	return (0);
}

void	launch_pipe(t_btree *node)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
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
	}
	else if ((tree->left != NULL && tree->left->arr != NULL)
		&& (tree->right != NULL && tree->right->arr != NULL)
		&& ft_strequ(tree->arg->word, "|"))
		launch_pipe(tree);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (0);
}
