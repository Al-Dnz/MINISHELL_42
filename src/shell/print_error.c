/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:39:07 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/27 20:11:22 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(void)
{
	if (g_data.status == 127)
	{
		write(2, g_data.token_err, ft_strlen(g_data.token_err));
		write(2, ": No such file or directory\n", 28);
	}
	if (g_data.status == 258)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, g_data.token_err, ft_strlen(g_data.token_err));
		write(2, "'\n", 2);
	}
	if (g_data.status == 1 && errno)
		perror(g_data.token_err);
}

void	print_err_env(char *s)
{
	g_data.status = 1;
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" not set\n", 2);
}

void	print_basic_error(void)
{
	g_data.status = 1;
	g_data.token_err = ft_strdup("minishell");
	print_error();
}

void	print_opt_error(char *opt)
{
	write(2, "minishell: cd: ", 15);
	write(2, opt, ft_strlen(opt));
	write(2, ": invalid option\n", 17);
}
