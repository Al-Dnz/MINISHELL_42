/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:12:58 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:12:59 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' );
}

int	is_pipe_op(char c)
{
	return (c == '|');
}

int	is_redir_op(char *str)
{
	return (ft_strequ(str, ">") || ft_strequ(str, "<") || ft_strequ(str, ">>")
		|| ft_strequ(str, "<<"));
}

int	is_word(char *str)
{
	if (str == NULL || is_redir_op(str) == 1 || ft_strequ(str, "|"))
		return (0);
	return (1);
}
