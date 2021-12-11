/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:26:35 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/11 00:40:16 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint(int n)
{
	(void)n;
	printf("\n");
//	rl_replace_line("", 0);

	rl_on_new_line();
	rl_redisplay();
}

static void	sigquit(int n)
{
	(void)n;
	printf("exit\n");
//	rl_replace_line("exit", 0);
	exit(g_data.err);
}

void	signal_manager(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}
