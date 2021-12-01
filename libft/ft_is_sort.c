/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:39:29 by adenhez           #+#    #+#             */
/*   Updated: 2021/06/09 13:39:04 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	define_sens(int i, int *tab, int (*f)(int, int))
{
	if ((*f)(tab[i], tab[i + 1]) > 0)
		return (1);
	else
		return (0);
}

int	ft_is_sort(int *tab, int length, int (*f)(int, int))
{
	int	i;
	int	sens;

	i = 0;
	if (length <= 1)
		return (1);
	while (tab[i] == tab[i + 1] && tab[i + 1])
		i++;
	if (!tab[i + 1])
		return (1);
	sens = define_sens(i, tab, f);
	while (i + 1 < length)
	{
		if (sens && (*f)(tab[i], tab[i + 1]) < 0)
			return (0);
		if (!sens && (*f)(tab[i], tab[i + 1]) > 0)
			return (0);
		i++;
	}
	return (1);
}
