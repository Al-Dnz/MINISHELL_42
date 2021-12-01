/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:48:18 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/01 17:53:42 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	ft_putstr_fd("[", 1);
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		ft_putstr_fd(", ", 1);
		i++;
	}
	ft_putstr_fd("NULL", 1);
	ft_putstr_fd("]", 1);
}

void	ft_print_tab2(char **tab)
{
	int	i;

	i = 0;
	ft_putstr_fd("[\n", 1);
	while (tab[i])
	{
		ft_putstr_fd("	", 1);
		ft_putstr_fd(tab[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	ft_putstr_fd("	", 1);
	ft_putstr_fd("NULL\n", 1);
	ft_putstr_fd("]", 1);
}
