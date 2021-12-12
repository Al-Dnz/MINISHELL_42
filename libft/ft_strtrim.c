/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 23:08:13 by adenhez           #+#    #+#             */
/*   Updated: 2020/11/19 23:21:03 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1);
	i = 0;
	if (!s1 || !set)
		return (0);
	while (s1[i] && ft_strchr((char *)set, s1[i]))
		i++;
	while (j && j > i && ft_strchr((char *)set, s1[j]))
		j--;
	result = ft_substr(s1, i, j - i + 1);
	return (result);
}
