/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 22:51:21 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/24 01:16:48 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

void	signal_handler(void)
{
	signal(SIGINT, &handler_sigint);
	signal(SIGCHLD, &handler_sigchild);
	signal(SIGQUIT, &handler_sigquit);
	data()->quit = 0;
}

void	handler_sigchild(int sig)
{
	pid_t	pid;
	int		status;

	(void)sig;
	pid = wait(&status);
	if (pid == -1)
		return ;
}

#ifdef __linux__

void	handler_sigint(int sig)
{
	if (sig == 2)
	{
		g_status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		if (data()->in_hdoc == 0)
		{
			write(1, "\n", 1);
			rl_redisplay();
		}
		else if (data()->in_hdoc == 1)
		{
			write(1, "\n", 1);
			clean_exit(130, 0);
		}
	}
}

#else

void	handler_sigint(int sig)
{
	(void)sig;
	// if (sig == 2)
	// {
		g_status = 130;
		rl_on_new_line();
		if (data()->in_hdoc == 0)
		{
			write(1, "\n", 1);
			rl_redisplay();
		}
		else if (data()->in_hdoc == 1)
		{
			write(1, "\n", 1);
			clean_exit(130, 0);
		}
	// }
}

#endif

void	handler_sigquit(int sig)
{
	int	status;
	int	tmp;

	(void)sig;
	// if (data()->child_pid == -1)
	// 	return ;
	tmp = waitpid(data()->child_pid, &status, WUNTRACED);
	if (tmp == -1)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
	}
	write(1, "Quit: (core dumped)\n", 20);
	rl_redisplay();
	data()->quit = 1;
	g_status = 131;
}
