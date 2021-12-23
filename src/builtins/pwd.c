/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:31:11 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/23 08:07:55 by adenhez          ###   ########.fr       */
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
		data()->token_err = ft_strdup("minishell: pwd");
		print_error();
	}
	data()->env = change_var(data()->env, "PWD=", buf);
	if (!data()->env)
	{
		g_status = 1;
		data()->token_err = ft_strdup("minishell");
		print_error();
	}
	if (print)
	{
		write(1, buf, ft_strlen(buf));
		write(1, "\n", 1);
	}
	ft_strclr(&buf);
	g_status = 0;
}
