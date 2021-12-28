/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:08:13 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:10:24 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_r(t_redir *tmp)
{
	int	fd;

	fd = open(tmp->file, O_RDONLY);
	if (fd == -1 && access(tmp->file, F_OK | R_OK) == -1)
	{
		printf("minishell: %s:", tmp->file);
		printf("no such file or directory or operation not permitted(r)\n");
		return (0);
	}
	close(fd);
	return (1);
}

int	check_file_w(t_redir *tmp)
{
	int	fd;

	fd = open(tmp->file, O_CREAT | O_RDWR | O_APPEND, S_IRWXU
			| S_IRWXG | S_IRWXO);
	if (fd == -1 && access(tmp->file, F_OK | W_OK) == -1)
	{
		printf("minishell: %s:", tmp->file);
		printf("no such file or directory or operation not permitted(w)\n");
		return (0);
	}
	close(fd);
	return (1);
}

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
			else if (tmp->kind == 1 && !check_file_r(tmp))
				return (0);
			else if ((tmp->kind == 2 || tmp->kind == 4) && !check_file_w(tmp))
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

/*
**	kind -> 1 2 3 4
**	dup2 -> 0 1 0 1
*/

int	launch_redir(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->kind == 1)
		fd = open(redir->file, O_RDONLY);
	else if (redir->kind == 2)
		fd = open(redir->file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU
				| S_IRWXG | S_IRWXO);
	else if (redir->kind == 3 && redir->hdoc_fd != -1)
		fd = redir->hdoc_fd;
	else if (redir->kind == 4)
		fd = open(redir->file, O_CREAT | O_RDWR | O_APPEND, S_IRWXU
				| S_IRWXG | S_IRWXO);
	dup2(fd, (redir->kind + 1) % 2);
	if (redir->next != NULL && redir->next->file != NULL)
	{
		close(fd);
		launch_redir(redir->next);
	}
	return (0);
}
