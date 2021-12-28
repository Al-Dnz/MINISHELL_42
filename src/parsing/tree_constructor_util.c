/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_constructor_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:12:45 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:12:46 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_node_cmd(t_btree **node, char *str)
{
	char	*new_str;

	new_str = token_cleaner(str);
	if (new_str == NULL)
		return (0);
	if (arg_add_back(&(*node)->arg, new_str) == 0)
	{
		ft_strclr(&new_str);
		return (0);
	}
	ft_strclr(&new_str);
	return (1);
}

int	save_node_redir(t_btree **node, char *str)
{
	if (redir_add_back(&(*node)->redir, str) == 0)
		return (0);
	return (1);
}

int	save_node_redir_file(t_btree **node, char *str)
{
	t_redir	*redir;
	t_redir	*tmp;
	char	*new_str;

	redir = (*node)->redir;
	if (redir == NULL)
		return (0);
	tmp = ft_redirlast(redir);
	new_str = token_cleaner(str);
	if (new_str == NULL)
		return (0);
	tmp->file = ft_strdup(new_str);
	ft_strclr(&new_str);
	if (tmp->file == NULL)
		return (0);
	return (1);
}
