/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_node_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:12:56 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:12:56 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_arg_tab(t_btree **tree)
{
	if ((*tree)->left != NULL)
		set_arg_tab(&(*tree)->left);
	if ((*tree)->right != NULL)
		set_arg_tab(&(*tree)->right);
	if (*tree != NULL && (*tree)->arg != NULL)
		(*tree)->arr = arglist_to_tab((*tree)->arg);
	else
		return ;
}

char	**arglist_to_tab(t_arg *arg)
{
	int		i;
	char	**arr;
	t_arg	*tmp;

	if (arg == NULL)
		return (NULL);
	i = 0;
	tmp = arg;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (i + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	tmp = arg;
	while (tmp)
	{
		arr[i++] = ft_strdup(tmp->word);
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}
