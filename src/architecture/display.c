/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:41:12 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/29 15:11:29 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_fd_list(t_fd_list *list)
{
	printf("fd_list: ");
	while (list != NULL)
	{
		printf("[%d]->", list->fd);
		list = list->next;
	}
	printf("NULL\n");
}

void	display_arg(t_arg *arg)
{
	printf("arg: ");
	while (arg != NULL)
	{
		printf("[%s]->", arg->word);
		arg = arg->next;
	}
	printf("NULL\n");
}

void	display_redir(t_redir *redir)
{
	static char	*sym_arr[6] = {"-1", "<", ">", "<<", ">>", 0};

	printf("redir: ");
	while (redir)
	{
		printf("[%s|%s]->", sym_arr[redir->kind], redir->file);
		redir = redir->next;
	}
	printf("NULL\n");
}

void	display_hdoc(t_hdoc *hdoc)
{
	printf("hdoc: ");
	while (hdoc != NULL)
	{
		printf("[%d|%s]->", hdoc->fd, hdoc->end_word);
		hdoc = hdoc->next;
	}
	printf("NULL\n");
}

void	display_tree(t_btree *node)
{
	static int	i;

	if (g_data.displayer == 0)
		i = 0;
	g_data.displayer = 1;
	if (i == 0)
		printf("[ROOT]");
	else if (i % 2)
		printf("[R]");
	else
		printf("[L]");
	printf("(%d)--------------------------------------------\n", i++);
	if (node == NULL)
	{
		printf("NULL\n");
		return ;
	}
	display_redir(node->redir);
	display_hdoc(node->hdoc);
	display_arg(node->arg);
	ft_putstr_fd("arr: ", 1);
	ft_print_tab(node->arr);
	ft_putstr_fd("\n", 1);
	display_tree(node->right);
	display_tree(node->left);
}
