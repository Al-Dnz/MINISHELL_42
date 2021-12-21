/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:31:11 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/21 22:30:07 by adenhez          ###   ########.fr       */
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
	g_data.env = change_var(g_data.env, "PWD=", buf);
	if (!g_data.env)
	{
		g_data.status = 1;
		g_data.token_err = ft_strdup("minishell");
		print_error();
	}
	if (print)
	{
		write(1, buf, ft_strlen(buf));
		write(1, "\n", 1);
	}
	ft_strclr(&buf);
	g_data.status = 0;
}
