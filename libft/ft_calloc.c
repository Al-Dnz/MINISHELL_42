/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:30:52 by adenhez           #+#    #+#             */
/*   Updated: 2020/11/10 23:49:11 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** create memory for count objects of size bytes
** and set each at 0.
*/

void	*ft_calloc(size_t count, size_t size)
{
	size_t	n;
	void	*mem;

	n = count * size;
	mem = malloc(n);
	if (mem == NULL)
		return (NULL);
	ft_memset(mem, 0, n);
	return (mem);
}
