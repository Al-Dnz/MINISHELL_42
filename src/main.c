/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:28:06 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/28 12:10:02 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

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
