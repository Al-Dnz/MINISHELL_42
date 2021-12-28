/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_suit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:34:00 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/28 21:24:26 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_suit(char *line, int i)
{
	int	x;

	x = 1;
	while (line [i + x] && line[i + x] == line[i])
		x++;
	if (x == 3)
	{
		if (line[i] == '<')
			g_data.token_err = ft_strdup("<");
		else if (line[i] == '>')
			g_data.token_err = ft_strdup(">");
		return (0);
	}
	else if (x > 3)
	{
		if (line[i] == '<')
			g_data.token_err = ft_strdup("<<");
		else if (line[i] == '>')
			g_data.token_err = ft_strdup(">>");
		return (0);
	}
	return (1);
}

int	check_syntax_ope(char *line, int i)
{
	if (!check_syntax_redir(line, i))
		return (0);
	if (!check_suit(line, i))
		return (0);
	return (1);
}
