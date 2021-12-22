/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 19:43:36 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/22 18:41:54 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab == NULL || *tab == NULL)
		return ;
	if (tab != NULL)
	{
		while (tab[++i] != NULL)
			free(tab[i]);
		free(tab[i]);
		free(tab);
		tab = NULL;
	}
}
