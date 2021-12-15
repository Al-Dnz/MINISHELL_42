#include "minishell.h"



int	launch_command(t_btree *node, char *cmd)
{
	if (node && cmd != 0)
	{
		// if ((ft_strcmp(cmd, "cd")) == 0)
		// {
		// 	cd(node->arg, &sg()->env);
		// }
		// else if ((ft_strcmp(cmd, "export")) == 0)
		// 	launch_export(node->arg, &sg()->env);
		// else if ((ft_strcmp(cmd, "unset")) == 0)
		// 	launch_unset(node->arg, &sg()->env);
		// else if ((ft_strcmp(cmd, "exit")) == 0)
		// 	ft_exit(node);
		// else if ((ft_strcmp(cmd, "pwd")) == 0)
		// 	pwd();
		// else if ((ft_strcmp(cmd, "echo")) == 0)
		// 	echo(node->arg);
		// else if ((ft_strcmp(cmd, "env")) == 0)
		// 	env(sg()->env);
		// else
			fork_execve(node);
	}
	return (0);
}

/*
	Execute two node command in pipe node
*/
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
	}
}

/*
	Execute ast recursively
*/
int	launch_tree(t_btree *tree)
{	
	if (tree->left == NULL && tree->right == NULL)
	{
		// if (tree->redir != NULL)
		// {
		// 	if (launch_redir(tree->redir) == -1)
		// 		return (-1);
		// }
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
