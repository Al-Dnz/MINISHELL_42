/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 23:07:44 by adenhez           #+#    #+#             */
/*   Updated: 2021/06/09 12:59:43 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlelen;
	size_t	haylen;
	size_t	index;

	needlelen = ft_strlen(needle);
	haylen = ft_strlen(haystack);
	index = 0;
	if (needlelen == 0)
		return ((char *)haystack);
	while ((index + needlelen - 1) < len && (index + needlelen - 1) < haylen)
	{
		if (haystack[index] == *needle)
			if (ft_strncmp(&haystack[index], needle, needlelen) == 0)
				return ((char *)&haystack[index]);
		index++;
	}
	return (NULL);
}
