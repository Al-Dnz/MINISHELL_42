/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:23:09 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/01 17:47:29 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	***matrix_gen(int n)
{
	char	***matrix_tab;

	matrix_tab = (char ***)malloc(sizeof(char **) * (n + 1));
	if (matrix_tab == NULL)
		return (NULL);
	matrix_tab[n] = NULL;
	return (matrix_tab);
}

void	ft_print_matrix(char ***matrix)
{
	int	i;

	i = 0;
	ft_putstr_fd("{", 1);
	while (matrix[i])
	{
		ft_putstr_fd("\n	", 1);
		ft_print_tab(matrix[i]);
		ft_putstr_fd(",", 1);
		i++;
	}
	ft_putstr_fd("\n	NULL\n", 1);
	ft_putstr_fd("}\n", 1);
}

void	free_matrix(char ***matrix_tab)
{
	int	i;

	i = -1;
	if (matrix_tab != NULL)
	{
		while (matrix_tab[++i] != NULL)
			ft_free_tab(matrix_tab[i]);
		free(matrix_tab[i]);
		free(matrix_tab);
		matrix_tab = NULL;
	}
}
