/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 20:07:10 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/23 08:07:42 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag(char *word)
{
	int	i;

	i = 0;
	if (word[i] != 0 && ft_strncmp(word, "-n", 2) == 0)
	{
		i++;
		while (word[i] && word[i] == 'n')
			i++;
		if (word[i] == '\0')
			return (1);
	}
	return (0);
}

void	echo(t_arg *arg)
{
	int		n;
	t_arg	*tmp;

	n = 0;
	tmp = arg;
	while (tmp->next && is_flag(tmp->next->word))
	{
		n = 1;
		tmp = tmp->next;
	}
	while (tmp->next)
	{
		write(1, tmp->next->word, ft_strlen(tmp->next->word));
		tmp = tmp->next;
		if (tmp->next && tmp->next->word)
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
	g_data.status = 0;
}
