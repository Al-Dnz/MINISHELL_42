/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 22:51:21 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/22 17:25:20 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

void	ft_signal(void)
{
	signal(SIGINT, &handler_sigint);
	signal(SIGQUIT, &handler_sigquit);
	signal(SIGCHLD, &handler_sigchild);
	g_data.quit = 0;
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

#ifdef LINUX

void	handler_sigint(int sig)
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

#else

void	handler_sigint(int sig)
{
	if (sig == 2)
	{
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
}

#endif

void	handler_sigquit(int sig)
{
	int	status;
	int	tmp;

	(void)sig;
	tmp = waitpid(g_data.child_pid, &status, WUNTRACED);
	if (tmp == -1)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
	}
	write(1, "Quit: (core dumped)\n", 21);
	rl_redisplay();
	g_data.quit = 1;
	g_data.status = 131;
}

void	ctrl_d(void)
{
	int	status;

	write(1, "exit\n", 5);
	status = g_data.status;
	clean_program();
	exit(status);
}
