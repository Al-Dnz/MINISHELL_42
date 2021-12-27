#include "minishell.h"

int	launch_command(t_btree *node, char *cmd)
{
	if (node && cmd != 0)
	{
		if (!ft_strcmp(cmd, "echo"))
			echo(node->arg);
		else if (!ft_strcmp(cmd, "env"))
			cmd_env(node->arg);
		else if (!ft_strcmp(cmd, "pwd"))
			pwd(1);
		else if (!ft_strcmp(cmd, "cd"))
			cd(node->arg);
		else if (!ft_strcmp(cmd, "export"))
			export(node->arg);
		else if (!ft_strcmp(cmd, "unset"))
			unset(node->arg);
		else if (!ft_strcmp(cmd, "exit"))
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
		pid = waitpid(0, &g_data.chd_status, 0);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		launch_tree(node->right);
		close(pipe_fd[0]);
		clean_program();
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
