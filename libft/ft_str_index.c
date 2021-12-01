/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:10:17 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 17:56:00 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_index(char *str, char **tab)
{
	int	index;

	index = 0;
	while (tab[index])
	{
		if (ft_strcmp(str, tab[index]) == 0)
			return (index);
		index++;
	}
	return (-1);
}
