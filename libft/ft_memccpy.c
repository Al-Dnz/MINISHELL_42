/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:42:38 by adenhez           #+#    #+#             */
/*   Updated: 2021/06/09 12:57:20 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t size)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			i;

	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		if (dst[i] == (unsigned char)c)
			return ((void *)(&(dst[i + 1])));
		i++;
	}
	return (NULL);
}
