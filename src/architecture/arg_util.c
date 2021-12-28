/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:41:08 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/28 12:41:09 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*new_arg(char *str)
{
	t_arg	*element;

	element = malloc(sizeof(t_arg));
	if (element == NULL)
		return (NULL);
	element->word = ft_strdup(str);
	if (element->word == NULL)
	{
		free(element);
		return (NULL);
	}
	element->next = NULL;
	return (element);
}

void	del_arg(t_arg *arg)
{
	if (arg == NULL)
		return ;
	ft_strclr(&arg->word);
}

void	arg_clr(t_arg **arg)
{
	t_arg	*tmp;

	if (*arg == NULL)
		return ;
	if ((*arg)->next != NULL)
		tmp = (*arg)->next;
	else
		tmp = NULL;
	del_arg(*arg);
	free(*arg);
	*arg = tmp;
	arg_clr(&(*arg));
}

t_arg	*ft_arglast(t_arg *arg)
{
	if (arg == NULL)
		return (NULL);
	while (arg->next != NULL)
		arg = arg->next;
	return (arg);
}

int	arg_add_back(t_arg **arg, char *str)
{
	t_arg	*element;
	t_arg	*tmp;

	element = new_arg(str);
	if (element == NULL)
		return (0);
	if (*arg == NULL)
	{
		*arg = element;
		return (1);
	}
	else
	{
		tmp = ft_arglast(*arg);
		tmp->next = element;
	}
	return (1);
}
