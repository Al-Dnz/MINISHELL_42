/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:12:51 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:12:51 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unquoted_string_size(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_quote(str[len]))
		len++;
	return (len);
}

int	quoted_string_size(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (-1);
}

int	operator_size(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '|')
		return (i + 1);
	else if (line[i] == '>' || line[i] == '<')
	{
		i++;
		if ((line[i - 1] == '>' && line[i] == '>')
			|| (line[i - 1] == '<' && line[i] == '<'))
			return (i + 1);
	}
	return (i);
}

/* 
	Get size of one token
*/
int	token_size(char *line)
{
	int	i;

	i = 0;
	if (is_operator(line[i]))
		return (i + operator_size(line + i));
	while (line[i] && line[i] != '\n' && line[i] != ' '
		&& !is_operator(line[i]))
	{
		if (is_quote(line[i]))
		{
			if (quoted_string_size(line + i, line[i]) > 0)
				i += quoted_string_size(line + i, line[i]);
			else
				return (0);
		}
		if (line[i] && line[i] != '\n' && line[i] != ' '
			&& !is_quote(line[i]) && !is_operator(line[i]))
			i++;
	}
	return (i);
}
