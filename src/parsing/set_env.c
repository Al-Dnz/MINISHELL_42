/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:08:53 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/28 12:10:12 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env(char **env)
{
	char	*s;

	s = NULL;
	g_data.env = dup_env(env);
	if (!g_data.env)
		return (0);
	if (exist(g_data.env, "SHLVL=") != -1)
	{
		s = ft_itoa(ft_atoi(getvar_val("SHLVL=", g_data.env)) + 1);
		if (s == NULL)
			return (0);
	}
	else
		s = ft_strdup("1");
	if (!change_var(g_data.env, "SHLVL=", s, 0))
	{
		ft_free_tab(g_data.env);
		g_data.env = NULL;
		ft_strclr(&s);
		return (0);
	}
	ft_strclr(&s);
	return (1);
}
