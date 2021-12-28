/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:00:38 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/28 11:49:27 by ivloisy          ###   ########.fr       */
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

char	*add_slash(char *name, char *new, int dd)
{
	char	*snew;
	char	*sd;

	sd = NULL;
	if (dd == 0)
	{
		snew = ft_strjoin(name, new);
		if (snew == NULL)
			return (NULL);
	}
	else
	{
		sd = ft_strjoin("/", new);
		if (sd == NULL)
			return (NULL);
		snew = ft_strjoin(name, sd);
		if (snew == NULL)
		{
			ft_strclr(&sd);
			return (NULL);
		}
	}
	if (sd)
		ft_strclr(&sd);
	return (snew);
}

int	change_var(char **tab, char *name, char *new, int dd)
{
	int		i;
	char	*snew;

	snew = add_slash(name, new, dd);
	if (snew == NULL)
		return (0);
	i = 0;
	while (tab[i] && i < ft_tabsize(tab))
	{
		if (!ft_strncmp(name, tab[i], ft_strlen(name)))
		{
			free (tab[i]);
			tab[i] = ft_strdup(snew);
		}
		i++;
	}
	ft_strclr(&snew);
	return (1);
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
