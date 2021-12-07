/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:42:55 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/07 17:26:30 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_pipe1(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		if (line[i + 1] && line[i + 1] == '|')
		{
			g_data.token_err = "||";
			return (0);
		}
		g_data.token_err = "|";
		return (0);
	}
	return (1);
}

static int check_pipe2(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != '|')
		i++;
	if (line[i] == '|' && line[i + 1])
	{
		i++;
/*
	if "||" not accepted
*/
		if (line[i] == '|')
		{
			g_data.token_err = "||";
			return (0);
		}//
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '|' || !line[i])
		{
			g_data.token_err = "|";
			return (0);
		}
	}
	else if (line[i] == '|' && !line[i + 1])
	{
		g_data.token_err = "|";
		return (0);
	}
	return (1);
}

int check_syntax(char *line)
{
	if (line)
	{
		if (!check_pipe1(line) || !check_pipe2(line))
		{
			g_data.err = 258;
			return (0);
		}
	}
	return (1);
}