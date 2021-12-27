/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:31:11 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/27 17:02:12 by ivloisy          ###   ########.fr       */
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
		g_status = 1;
		data()->token_err = ft_strdup("minishell");
		print_error();
	}
	else
	{
		if (exist(data()->env, "PWD=") != -1)
		{
			if (!change_var(data()->env, "PWD=", buf, data()->dd))
			{
				g_status = 1;
				data()->token_err = ft_strdup("minishell");
				print_error();
				ft_strclr(&buf);
				return ;
			}
		}
		if (print)
		{
			if (exist(data()->env, "PWD=") == -1)
				printf("%s\n", buf);
			else
				printf("%s\n", getvar_val("PWD=", data()->env));
		}
		ft_strclr(&buf);
		g_status = 0;
	}
}
