/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_hdoc_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:08:08 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:08:08 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_rdl_str(void)
{
	free(g_data.str);
	g_data.str = NULL;
	clean_process();
	return (NULL);
}

char	*str_error2(char *s, char *ret, int status)
{
	ft_putendl_fd(s, 2);
	g_data.status = status;
	return (ret);
}

int	is_last_hdoc(t_redir *redir)
{
	if (redir == NULL)
		return (1);
	redir = redir->next;
	while (redir != NULL)
	{
		if (redir->kind == 3)
			return (0);
		redir = redir->next;
	}
	return (1);
}

int	set_fd_redir(t_btree *node, int fd)
{
	t_redir	*redir;

	redir = node->redir;
	while (redir != NULL)
	{
		if (redir->kind == 3 && is_last_hdoc(redir) == 1)
		{
			redir->hdoc_fd = fd;
			return (0);
		}
		redir = redir->next;
	}
	return (1);
}
