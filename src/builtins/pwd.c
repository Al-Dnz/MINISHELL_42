/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:31:11 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/14 12:29:11 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf == NULL)
	{
		g_data.err = 1;
		print_error();
	}
	else
	{
		write(1, buf, ft_strlen(buf));
		write(1, "\n", 1);
		g_data.err = 0;
	}
}
