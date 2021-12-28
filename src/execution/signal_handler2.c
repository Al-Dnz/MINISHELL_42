/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:07:37 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:09:01 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_by_signal(void)
{
	write(1, "\nexit\n", 6);
	clean_program();
	exit(g_data.status);
}

void	signal_handler(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGCHLD, &sigchild_handler);
	signal(SIGQUIT, &sigquit_handler);
	g_data.quit = 0;
}
