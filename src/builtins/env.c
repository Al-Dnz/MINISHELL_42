/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:30:19 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/29 16:22:42 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_char(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '-')
			return (i);
		i++;
	}
	return (0);
}

void	print_env(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	cmd_env(t_arg *arg)
{
	if (arg->next)
	{
		g_data.status = 1;
		if (arg->next->word && arg->next->word[0] == '-'
			&& ft_strlen(arg->next->word) > 1 && next_char(arg->next->word))
		{
			write(2, "env: illegal option -- ", 23);
			write(2, &arg->next->word[next_char(arg->next->word)], 1);
			write(2, "\n", 1);
		}
		else if (arg->next->word)
		{
			g_data.token_err = ft_strjoin("env: ", arg->next->word);
			g_data.status = 127;
			print_error();
		}
	}
	else
	{
		print_env(g_data.env);
		g_data.status = 0;
	}
}
