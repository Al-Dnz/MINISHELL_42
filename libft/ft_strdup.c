/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 23:05:11 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/12 16:35:55 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	int		i;
	char	*new;

	size = 0;
	while (s1[size])
		size++;
	new = malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strdup_special(const char *s)
{
	int		i;
	char	*new_s;

	if (!s)
		return (ft_calloc(sizeof(*new_s), (1)));
	i = ft_strlen(s);
	new_s = ft_calloc(sizeof(*new_s), (i + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	return (new_s);
}
