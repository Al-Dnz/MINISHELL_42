/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 23:09:00 by adenhez           #+#    #+#             */
/*   Updated: 2020/11/13 12:10:04 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	if (!len || dst == src)
		return (dst);
	if (s2 < s1)
	{
		while (++i <= len)
			s1[len - i] = s2[len - i];
	}
	else
	{
		while (len-- > 0)
			*(s1++) = *(s2++);
	}
	return (dst);
}
