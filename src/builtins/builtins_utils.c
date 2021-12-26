/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:23:34 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/26 17:59:46 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_zero(char *s, int z)
{
	int		i;
	int		j;
	char	*n;

	i = 0;
	j = 0;
	n = (char *)malloc(sizeof(char) * (ft_strlen(s) - z + 1));
	if (n == NULL)
		return (NULL);
	if (s[i] == '-' || s[i] == '+')
	{
		n[i] = s[i];
		i++;
	}
	while (s[i] && s[i] == '0')
			i++;
	while (s[i])
	{
		n[i - z] = s[i];
		i++;
	}
	n[i - z] = '\0';
	return (n);
}

char	*split_zero(char *s)
{
	int		z;
	int		i;
	char	*n;

	z = 0;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && s[i] == '0')
	{
		z++;
		i++;
	}
	if (s[i] == '\0')
		n = ft_strdup("0");
	else
		n = del_zero(s, z);
	return (n);
}
