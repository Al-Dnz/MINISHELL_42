/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 19:43:36 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/14 22:41:44 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab == NULL)
		return ;
	if (tab != NULL)
	{
		while (tab[++i] != 0)
			free(tab[i]);
		free(tab[i]);
		free(tab);
		tab = NULL;
	}
}
