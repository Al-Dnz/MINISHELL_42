/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:47:51 by adenhez           #+#    #+#             */
/*   Updated: 2021/05/24 22:48:52 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstshift(t_list **head)
{
	t_list	*second_last;
	void	*result;

	second_last = NULL;
	if (head == NULL || *head == NULL)
		return (NULL);
	if ((*head)->next == NULL)
	{
		return (ft_lstpop(head));
	}
	second_last = *head;
	while (second_last->next->next != NULL)
		second_last = second_last->next;
	result = second_last->next->content;
	ft_lstdelone(second_last->next, &ft_del);
	second_last->next = NULL;
	return (result);
}
