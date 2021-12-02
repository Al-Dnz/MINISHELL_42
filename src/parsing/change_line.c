/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:17:01 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/02 22:21:03 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_line(t_ms *ms)
{
	int		i;

	i = 0;
	ms->copy = ft_strdup(ms->line);
	if (!ms->copy)
	{
		ms->error = BASIC_ERROR;
		return (0);
	}
	while (ms->copy[i])
	{
		//if (check_quote(ms->line, i))
		i++;
	}
    return (1);
}