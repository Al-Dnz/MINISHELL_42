/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 22:51:21 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:57:52 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

void	sigchild_handler(int sig)
{
	pid_t	pid;
	int		status;

	(void)sig;
	pid = wait(&status);
	if (pid == -1)
		return ;
}

#ifdef __linux__

void	sigint_handler(int sig)
{
	if (sig == 2)
	{
		g_data.status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_data.in_hdoc == 0)
		{
			write(1, "\n", 1);
			rl_redisplay();
		}
		else if (g_data.in_hdoc == 1)
		{
			write(1, "\n", 1);
			clean_exit(130, 0);
		}
	}
}

void	sigquit_handler(int sig)
{
	int	status;
	int	tmp;

	(void)sig;
	tmp = 0;
	tmp = waitpid(g_data.child_pid, &status, WUNTRACED);
	if (tmp == -1)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
	}
	write(1, "Quit: (core dumped)\n", 20);
	rl_redisplay();
	g_data.quit = 1;
	g_data.status = 131;
	clean_process();
}

#else

void	sigint_handler(int sig)
{
	(void)sig;
	g_data.status = 130;
	rl_on_new_line();
	if (g_data.in_hdoc == 0)
	{
		write(1, "\n", 1);
		rl_redisplay();
	}
	else if (g_data.in_hdoc == 1)
	{
		write(1, "\n", 1);
		clean_exit(130, 0);
	}
}

void	sigquit_handler(int sig)
{
	int	status;
	int	tmp;

	(void)sig;
	if (g_data.child_pid == -1)
		return ;
	tmp = 0;
	tmp = waitpid(g_data.child_pid, &status, WUNTRACED);
	if (tmp == -1)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
	}
	write(1, "Quit: (core dumped)\n", 20);
	rl_redisplay();
	g_data.quit = 1;
	g_data.status = 131;
	clean_process();
}

#endif
