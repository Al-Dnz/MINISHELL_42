/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:31:11 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/27 18:10:58 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_init(int print)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf == NULL)
	{
		g_data.status = 1;
		g_data.token_err = ft_strdup("minishell");
		print_error();
	}
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
		{
			if (exist(g_data.env, "PWD=") == -1)
				printf("%s\n", buf);
			else
				printf("%s\n", getvar_val("PWD=", g_data.env));
		}
		ft_strclr(&buf);
		g_data.status = 0;
	}
}


void	pwd(int print)
{
/* 	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0); */
	char	*value;
	char	s[4000];

	value = getcwd(s, 4000);
	if (value == NULL)
	{
		g_data.status = 1;
		g_data.token_err = ft_strdup("minishell");
		print_error();
	}
	else
	{
		if (exist(g_data.env, "PWD=") != -1)
		{
			if (!change_var(g_data.env, "PWD=", value, g_data.dd))
			{
				g_data.status = 1;
				g_data.token_err = ft_strdup("minishell");
				ft_strclr(&value);
				print_error();
				return ;
			}
		}
		if (print)
		{
			if (exist(g_data.env, "PWD=") == -1)
				printf("%s\n", value);
			else
				printf("%s\n", getvar_val("PWD=", g_data.env));
		}
		ft_strclr(&value);
		g_data.status = 0;
	}
}
