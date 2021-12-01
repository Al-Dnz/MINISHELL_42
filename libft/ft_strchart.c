/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:27:02 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/29 19:27:22 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchart(char *str, char *chart)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_find_index(chart, str[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}
