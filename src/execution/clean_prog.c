/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:07:42 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/29 14:06:01 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_program(void)
{
	ft_free_tab(g_data.token_tab);
	g_data.token_tab = NULL;
	ft_free_tab(g_data.env);
	g_data.env = NULL;
	free_btree(g_data.tree);
	g_data.tree = NULL;
	ft_strclr(&g_data.str);
	if (g_data.token_err)
		ft_strclr(&g_data.token_err);
	g_data.str = NULL;
	fd_list_clr(&g_data.fd_list);
}

void	clean_process(void)
{
	ft_free_tab(g_data.token_tab);
	g_data.token_tab = NULL;
	free_btree(g_data.tree);
	g_data.tree = NULL;
	ft_strclr(&g_data.str);
	if (g_data.token_err)
		ft_strclr(&g_data.token_err);
	g_data.str = NULL;
	fd_list_clr(&g_data.fd_list);
}
