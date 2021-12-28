/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:23:34 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/28 15:18:44 by adenhez          ###   ########.fr       */
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

int	ft_str_isalnum_eq(char *s)
{
	int	i;

	if (!s)
		return (-1);
	if (s[0] == '_' || ft_isalpha(s[0]))
	{
		i = 1;
		while (s[i])
		{
			if (s[i] != '_' && !ft_isalnum(s[i]))
				return (0);
			i++;
		}
	}
	else
	{
		i = 0;
		while (s[i])
		{
			if (!ft_isalpha(s[i]) && s[i] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}
