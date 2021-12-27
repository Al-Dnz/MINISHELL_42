/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:28:06 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/27 23:08:36 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

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

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	g_data.status = 0;
	if (env[0] == NULL)
	{
		ft_putstr_fd("minishell execution needs env paremeters\n", 2);
		return (EXIT_FAILURE);
	}
	if (isatty(0) == 0)
	{
		ft_putstr_fd("open the minishell before execute commands\n", 2);
		return (EXIT_FAILURE);
	}
	if (argc > 1)
	{
		ft_putstr_fd("minishell doesn't take arguments\n", 2);
		return (EXIT_SUCCESS);
	}
	if (!set_env(env))
		return (0);
	main_loop(env);
	return (g_data.status);
}
