#include "minishell.h"

int	valid_redir(t_btree *node)
{
	t_redir	*tmp;

	if (node->right != NULL)
		valid_redir(node->right);
	if (node->left != NULL)
		valid_redir(node->left);
	if (node != NULL)
	{
		tmp = node->redir;
		while (tmp != NULL)
		{
			if (tmp->file == NULL)
			{
				write(1, "probleme redir\n", 15);
				return (0);
			}
				// SECURE CODE
			tmp = tmp->next;
		}
	}
	return (1);
}

int	launch_redir(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->kind == 1)
		fd = open(redir->file, O_RDONLY);
	else if (redir->kind == 2)
		fd = open(redir->file, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO);
	else if (redir->kind == 3 && redir->hdoc_fd != -1)
		fd = redir->hdoc_fd;
	else if (redir->kind == 4)
		fd = open(redir->file, O_CREAT|O_RDWR|O_APPEND, S_IRWXU|S_IRWXG|S_IRWXO);
	dup2(fd, (redir->kind + 1) % 2);
	if (redir->next != NULL && redir->next->file != NULL)
	{
		close(fd);
		launch_redir(redir->next);
	}
	return (0);
}