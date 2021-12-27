/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:39:07 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/27 13:53:32 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(void)
{
	if (g_status == 127)
	{
		write(2, data()->token_err, ft_strlen(data()->token_err));
		write(2, ": No such file or directory\n", 28);
	}
	if (g_status == 258)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, data()->token_err, ft_strlen(data()->token_err));
		write(2, "'\n", 2);
	}
	if (g_status == 1 && errno)
		perror(data()->token_err);
}

void	print_err_env(char *s)
{
	g_status = 1;
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" not set\n", 2);
}
