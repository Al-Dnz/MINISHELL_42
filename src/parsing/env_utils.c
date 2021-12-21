/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:00:38 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/21 01:03:06 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist(char **tab, char *name)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!strncmp(tab[i], name, ft_strlen(name)))
			return (i);
		i++;
	}
	return (-1);
}

char	**change_var(char **tab, char *name, char *new)
{
	int		i;

	i = 0;
	while (tab[i] && ft_strncmp(name, tab[i], ft_strlen(name))
		&& i < ft_tabsize(tab))
		i++;
	if (!tab[i])
	{
		ft_free_tab(tab);
		return (NULL);
	}
	else if (!ft_strncmp(name, tab[i], ft_strlen(name)))
	{
		tab[i] = ft_strjoin(name, new);
		if (!tab[i])
		{
			tab[i] = ft_strdup("");
			ft_free_tab(tab);
			return (NULL);
		}
	}
	return (tab);
}

char	*getvar_val(char *name, char **tab)
{
	char	*val;
	int		i;

	i = 0;
	while (tab[i] && ft_strncmp(name, tab[i], ft_strlen(name))
		&& i < ft_tabsize(tab))
		i++;
	if (tab[i] && !ft_strncmp(name, tab[i], ft_strlen(name)))
		return (val = tab[i] + ft_strlen(name));
	return (NULL);
}

char	**dup_env(char **tab)
{
	char	**new;
	int		i;
	int		err;

	if (!tab)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (ft_tabsize(tab) + 1));
	if (!new)
		return (NULL);
	err = 0;
	i = 0;
	while (tab[i] && !err)
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
			err = 1;
		i ++;
	}
	if (err)
	{
		ft_free_tab(new);
		return (NULL);
	}
	new[i] = NULL;
	return (new);
}
