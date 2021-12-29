/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:07:59 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/29 16:26:03 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all(void)
{
	int	fd;

	fd = 3;
	while (fd < 11)
		close(fd++);
}

void	error_cmd(char *cmd, int fd, int status)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(": ", fd);
	error_message("command not found", fd, status);
}

void	error_message(char *str, int fd, int status)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	g_data.exit_status = status;
}

#ifdef __linux__

void	clean_exit(int status, int error)
{
	if (error == 1 || error == 2)
		status = 2;
	rl_clear_history();
	close(g_data.std_in);
	close(g_data.std_out);
	clean_program();
	close(g_data.std_in);
	close(g_data.std_out);
	exit(status);
}

#else

void	clean_exit(int status, int error)
{
	if (error == 1 || error == 2)
		status = 2;
	close(g_data.std_in);
	close(g_data.std_out);
	clean_program();
	exit(status);
}

#endif
