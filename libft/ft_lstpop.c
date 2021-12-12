/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:03:22 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/29 17:06:54 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstpop(t_list **head_ref)
{
	t_list	*head;
	void	*result;

	head = NULL;
	if (*head_ref == NULL)
		return (NULL);
	head = *head_ref;
	result = head->content;
	(*head_ref) = (*head_ref)->next;
	free(head);
	return (result);
}
