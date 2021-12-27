/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:12:28 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/27 17:31:17 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_valid(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (arg[i] != '\0' || arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			break ;
		i++;
	}
	if (arg[i] != '=' && arg[i] != '\0')
		return (0);
	if (arg[i] == '\0')
		return (-1);
	return (i);
}

static int	add_var(t_arg *arg)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (ft_tabsize(g_data.env) + 2));
	if (!tmp)
	{
		g_data.status = 1;
		return (0);
	}
	i = -1;
	while (g_data.env[++i])
		tmp[i] = ft_strdup(g_data.env[i]);
	tmp[i] = ft_strdup(arg->word);
	tmp[i + 1] = NULL;
	ft_free_tab(g_data.env);
	g_data.env = dup_env(tmp);
	if (!g_data.env)
	{
		g_data.status = 1;
		return (0);
	}
	ft_free_tab(tmp);
	return (1);
}

static int	update_env(t_arg *arg, int eq)
{
	char	*name;
	char	*val;

	name = ft_substr(arg->word, 0, eq + 1);
	val = ft_strdup(arg->word + eq + 1);
	if (exist(g_data.env, name) != -1)
	{
		if (!change_var(g_data.env, name, val, 0))
		{
			g_data.status = 1;
			return (0);
		}
	}
	else
	{
		if (!add_var(arg))
			return (0);
	}
	ft_strclr(&name);
	ft_strclr(&val);
	return (1);
}

static int	check_arg(t_arg *arg)
{
	int	eq;

	if (arg->word)
	{
		eq = check_valid(arg->word);
		if (eq == -1)
			return (1);
		else if (eq > 0)
		{
			if (!update_env(arg, eq))
			{
				print_error();
				return (0);
			}
		}
		else
		{
			(g_data.token_err) = ft_strjoin("minishell: export: `", arg->word);
			write (2, g_data.token_err, ft_strlen(g_data.token_err));
			write (2, "': not a valid identifier\n", 26);
			g_data.status = 1;
			return (0);
		}
	}
	return (1);
}

void	export(t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg;
	if (!tmp->next)
		print_env(g_data.env);
	while (tmp->next)
	{
		tmp = tmp->next;
		if (!check_arg(tmp))
			return ;
	}
	g_data.status = 0;
}
