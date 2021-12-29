/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:42:55 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/29 15:57:47 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe(char *line, int i)
{
	int	j;

	j = 0;
	while (line[j] && j < i)
	{
		if (line[j] != ' ')
			return (1);
		j++;
	}
	if (line[i + 1] && line[i + 1] == '|')
		g_data.token_err = ft_strdup("||");
	else
		g_data.token_err = ft_strdup("|");
	return (0);
}

static int	check_pipe2(char *line, int i)
{
	if (line[i] == '|' && line[i + 1])
	{
		i++;
		if (line[i] == '|')
		{
			g_data.token_err = ft_strdup("||");
			return (0);
		}
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '|' || !line[i])
		{
			if (line[i + 1] == '|')
				g_data.token_err = ft_strdup("||");
			else
				g_data.token_err = ft_strdup("|");
			return (0);
		}
	}
	else if (line[i] == '|' && !line[i + 1])
	{
		g_data.token_err = ft_strdup("|");
		return (0);
	}
	return (1);
}

static int	check_operator(char *line, int i)
{
	if ((line[i] == '|' && !check_pipe(line, i))
		|| (line[i] == '|' && !check_pipe2(line, i)))
		return (0);
	if ((line[i] == '<' || line[i] == '>') && !check_suit(line, i))
		return (0);
	if ((line[i] == '<' || line[i] == '>') && !check_syntax_redir(line, i))
		return (0);
	if (line[i] == '\\')
	{
		g_data.token_err = ft_strdup("\\");
		return (0);
	}
	if (line[i] == ';')
	{
		g_data.token_err = ft_strdup(";");
		return (0);
	}
	if (line[i] == '&' && line[i + 1] && line[i + 1] == '&')
	{
		g_data.token_err = ft_strdup("&&");
		return (0);
	}
	return (1);
}

static int	check_good_char(char *line, int i)
{
	if ((is_operator(line[i]) || line[i] == '\\' || line[i] == ';'
			|| line[i] == '&') && !check_operator(line, i))
	{
		g_data.status = 258;
		return (0);
	}
	return (1);
}

int	check_syntax(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			if (quoted_string_size(line + i, line[i]) != -1)
				i += quoted_string_size(line + i, line[i]);
			else
			{
				g_data.token_err = ft_substr(line, i, 1);
				g_data.status = 258;
				return (0);
			}
		}
		else
		{
			if (!check_good_char(line, i))
				return (0);
			i++;
		}
	}
	return (1);
}
