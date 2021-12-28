/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:41:18 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/28 12:41:24 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(char *str)
{
	t_redir		*element;
	static char	*sym_arr[5] = {"<", ">", "<<", ">>", 0};

	element = malloc(sizeof(t_redir));
	if (element == NULL)
		return (NULL);
	if (ft_str_index(str, sym_arr) != -1)
		element->kind = ft_str_index(str, sym_arr) + 1;
	else
		element->kind = 0;
	element->file = NULL;
	element->hdoc_fd = -1;
	element->next = NULL;
	return (element);
}

void	del_redir(t_redir *redir)
{
	if (redir == NULL)
		return ;
	ft_strclr(&redir->file);
	redir->hdoc_fd = 0;
}

void	redir_clr(t_redir **redir)
{
	t_redir	*tmp;

	if (*redir == NULL)
		return ;
	if ((*redir)->next != NULL)
		tmp = (*redir)->next;
	else
		tmp = NULL;
	del_redir(*redir);
	free(*redir);
	*redir = tmp;
	redir_clr(&(*redir));
}

t_redir	*ft_redirlast(t_redir *redir)
{
	if (redir == NULL)
		return (NULL);
	while (redir->next != NULL)
		redir = redir->next;
	return (redir);
}

int	redir_add_back(t_redir **redir, char *str)
{
	t_redir	*element;
	t_redir	*tmp;

	element = new_redir(str);
	if (element == NULL)
		return (0);
	if ((*redir) == NULL)
	{
		(*redir) = element;
		return (1);
	}
	else
	{
		tmp = ft_redirlast(*redir);
		tmp->next = element;
	}
	return (1);
}
