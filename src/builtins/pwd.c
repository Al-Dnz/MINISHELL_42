/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:31:11 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/25 20:07:46 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(int print)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf == NULL)
	{
		g_data.status = 1;
		g_data.token_err = ft_strdup("minishell: pwd");
		print_error();
	}
	if (!change_var(g_data.env, "PWD=", buf, g_data.dd))
	{
		g_data.status = 1;
		g_data.token_err = ft_strdup("minishell");
		print_error();
	}
	if (print)
	{
		write(1, getvar_val("PWD=", g_data.env),
			ft_strlen(getvar_val("PWD=", g_data.env)));
		write(1, "\n", 1);
	}
	ft_strclr(&buf);
	g_data.status = 0;
}
