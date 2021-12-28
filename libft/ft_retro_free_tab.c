/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retro_free_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:55:22 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/28 11:29:47 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_retro_free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
		i++;
	i++;
	free(tab[i]);
	while (--i >= 0)
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
	}
	free(tab);
	tab = NULL;
}
