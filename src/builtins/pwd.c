/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:31:11 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/13 21:51:09 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*path;
	char	s[4096];

	path = getcwd(s, 4096);
	if (path == NULL)
	{
		g_data.err = 1;
		print_error();
	}
	else
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		g_data.err = 0;
	}
}
