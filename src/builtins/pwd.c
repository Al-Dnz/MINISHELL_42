/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:31:11 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/27 19:53:58 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_pwd(char *s)
{
	if (exist(g_data.env, "PWD=") == -1)
		printf("%s\n", s);
	else
		printf("%s\n", getvar_val("PWD=", g_data.env));
}

void	pwd(int print)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf == NULL)
		print_basic_error();
	else
	{
		if (exist(g_data.env, "PWD=") != -1)
		{
			if (!change_var(g_data.env, "PWD=", buf, g_data.dd))
			{
				g_data.status = 1;
				g_data.token_err = ft_strdup("minishell");
				ft_strclr(&buf);
				print_error();
				return ;
			}
		}
		if (print)
			print_pwd(buf);
		ft_strclr(&buf);
		g_data.status = 0;
	}
}
