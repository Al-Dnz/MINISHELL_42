/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:41:21 by adenhez           #+#    #+#             */
/*   Updated: 2021/06/09 13:02:16 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*li;

	if (*lst == NULL)
		return ;
	if ((*lst)->next != NULL)
		li = (*lst)->next;
	else
		li = NULL;
	del((*lst)->content);
	free(*lst);
	*lst = li;
	ft_lstclear(&(*lst), del);
}
