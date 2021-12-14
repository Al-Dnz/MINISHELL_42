/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:39:07 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/14 18:39:54 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(void)
{
	if (g_data.err == 258)
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, g_data.token_err, ft_strlen(g_data.token_err));
		write(2, "'\n", 2);
/* 		 `%s'\n",
			g_data.token_err); */
}