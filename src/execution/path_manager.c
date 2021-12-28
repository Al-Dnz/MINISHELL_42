/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:08:05 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:08:05 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_unset(char *str)
{
	int		i;
	char	**tab;

	tab = g_data.env;
	i = 0;
	if (tab == NULL)
		return (0);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], str, ft_strlen(str))
			&& tab[i][ft_strlen(str)] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	formalize_env_path(char **env_tab)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env_tab[i])
	{
		temp = malloc(sizeof(char) * (ft_strlen(env_tab[i]) + 2));
		if (temp == NULL)
			return ;
		j = 0;
		while (env_tab[i][j])
		{
			temp[j] = env_tab[i][j];
			j++;
		}
		temp[j++] = '/';
		temp[j] = 0;
		ft_strclr(&env_tab[i]);
		env_tab[i] = temp;
		i++;
	}
}

char	*find_path(char *cmd)
{
	char	*path;
	char	*env;
	char	**env_tab;
	int		i;

	env = getenv("PATH");
	if (env == NULL || is_env_unset("PATH") == 1)
		return (NULL);
	env_tab = ft_split(env, ":");
	formalize_env_path(env_tab);
	i = 0;
	path = ft_strdup(cmd);
	while (access(path, F_OK | R_OK | X_OK) != 0 && env_tab[i])
	{
		ft_strclr(&path);
		path = ft_strjoin(env_tab[i], cmd);
		if (path == NULL)
			return (NULL);
		i++;
	}
	ft_free_tab(env_tab);
	if (access(path, F_OK | R_OK | X_OK) != 0)
		ft_strclr(&path);
	return (path);
}
