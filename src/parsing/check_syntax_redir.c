/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 01:18:52 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/28 20:20:36 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_end(char *line, int i)
{
	i++;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	check_ope(char *line, int i)
{
	if (line[i + 1] && line[i + 1] == line[i])
	{
		i++;
		if (line[i] == '>')
			g_data.token_err = ft_strdup(">>");
		else
		{
			if (line[i + 1] && line[i + 1] == line[i])
				g_data.token_err = ft_strdup("<<<");
			else
				g_data.token_err = ft_strdup("<<");
		}
	}
	else if (line[i + 1] && line[i + 1] == '>' && line[i] == '<')
		g_data.token_err = ft_strdup("<>");
	else
	{
		if (line[i] == '<')
			g_data.token_err = ft_strdup("<");
		else
			g_data.token_err = ft_strdup(">");
	}
	return (0);
}

static int	check_next(char *line, int i)
{
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (is_operator(line[i]))
	{
		if (line[i] == '|')
		{
			if (line[i + 1] && line[i + 1] == '|')
				g_data.token_err = ft_strdup("||");
			else
				g_data.token_err = ft_strdup("|");
			return (0);
		}
		else if ((line[i] == '<' || line[i] == '>') && !check_ope(line, i))
			return (0);
	}
	return (1);
}

static int	check_end(char *line, int i)
{
	i++;
	if (is_end(line, i))
	{
		g_data.token_err = ft_strdup("newline");
		return (0);
	}
	else if (line[i + 1] == line[i])
	{
		i++;
		if (is_end(line, i))
		{
			if (line[i] == '<' && line[i] == line[i - 1])
				g_data.token_err = ft_strdup("newline");
			else
				g_data.token_err = ft_strdup(">");
			return (0);
		}
		else if (!check_next(line, i))
			return (0);
	}
	else if (line[i + 1] != line[i] && !check_next(line, i))
		return (0);
	return (1);
}

int	check_syntax_redir(char *line, int i)
{
	if (is_end(line, i))
	{
		g_data.token_err = ft_strdup("newline");
		return (0);
	}
	else if (line[i + 1] == line[i] && !check_end(line, i))
		return (0);
	else if (line[i + 1] != line[i] && !check_next(line, i))
		return (0);
	return (1);
}
