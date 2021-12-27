/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:07:59 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:12:07 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (error == 1)
		error_message("minishell: exit: too many arguments", 2, 2);
	else if (error == 2)
		error_message("minishell: exit: need numeric argument", 2, 2);
	else if (error == 3)
		error_message("minishell: function failed", 2, status);
	else if (error == 4)
		error_message("minishell: parse error", 2, status);
	if (error == 1 || error == 2)
		status = 2;
	rl_clear_history();
	clean_program();
	exit(status);
}

#else

void	clean_exit(int status, int error)
{
	if (error == 1)
		error_message("minishell: exit: too many arguments", 2, 2);
	else if (error == 2)
		error_message("minishell: exit: need numeric argument", 2, 2);
	else if (error == 3)
		error_message("minishell: function failed", 2, status);
	else if (error == 4)
		error_message("minishell: parse error", 2, status);
	if (error == 1 || error == 2)
		status = 2;
	//rl_clear_history();
	clean_program();
	exit(status);
}

#endif
