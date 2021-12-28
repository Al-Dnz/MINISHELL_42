/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:41:15 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/28 12:41:15 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hdoc	*new_hdoc(char *str)
{
	t_hdoc	*element;

	element = malloc(sizeof(t_hdoc));
	if (element == NULL)
		return (NULL);
	element->fd = -1;
	element->end_word = ft_strdup(str);
	element->next = NULL;
	return (element);
}

void	del_hdoc(t_hdoc *hdoc)
{
	if (hdoc == NULL)
		return ;
	ft_strclr(&hdoc->end_word);
}

void	hdoc_clr(t_hdoc **hdoc)
{
	t_hdoc	*tmp;

	if (*hdoc == NULL)
		return ;
	if ((*hdoc)->next != NULL)
		tmp = (*hdoc)->next;
	else
		tmp = NULL;
	del_hdoc(*hdoc);
	free(*hdoc);
	*hdoc = tmp;
	hdoc_clr(&(*hdoc));
}

t_hdoc	*ft_hdoclast(t_hdoc *hdoc)
{
	if (hdoc == NULL)
		return (NULL);
	while (hdoc->next != NULL)
		hdoc = hdoc->next;
	return (hdoc);
}

int	hdoc_add_back(t_hdoc **hdoc, char *str)
{
	t_hdoc	*element;
	t_hdoc	*tmp;

	element = new_hdoc(str);
	if (element == NULL)
		return (0);
	if ((*hdoc) == NULL)
	{
		(*hdoc) = element;
		return (1);
	}
	else
	{
		tmp = ft_hdoclast(*hdoc);
		tmp->next = element;
	}
	return (1);
}
