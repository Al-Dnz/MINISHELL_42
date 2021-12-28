/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_list_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 23:13:21 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/29 00:56:47 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd_list	*new_fd_list(int fd)
{
	t_fd_list		*element;

	element = malloc(sizeof(t_fd_list));
	if (element == NULL)
		return (NULL);
	element->fd = fd;
	element->next = NULL;
	return (element);
}

void	del_fd_list(t_fd_list *lst)
{
	if (lst == NULL)
		return ;
	if (lst->fd != 0 && lst->fd != 1)
		close(lst->fd);
}

void	fd_list_clr(t_fd_list **lst)
{
	t_fd_list	*tmp;

	if (*lst == NULL)
		return ;
	if ((*lst)->next != NULL)
		tmp = (*lst)->next;
	else
		tmp = NULL;
	del_fd_list(*lst);
	free(*lst);
	*lst = tmp;
	fd_list_clr(&(*lst));
}

t_fd_list	*ft_fd_listlast(t_fd_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	fd_lst_add_back(t_fd_list **lst, int fd)
{
	t_fd_list	*element;
	t_fd_list	*tmp;

	element = new_fd_list(fd);
	if (element == NULL)
		return (0);
	if (*lst == NULL)
	{
		*lst = element;
		return (1);
	}
	else
	{
		tmp = ft_fd_listlast(*lst);
		tmp->next = element;
	}
	return (1);
}
