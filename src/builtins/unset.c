/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:03:51 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/26 18:44:21 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	twist_tab(char **tmp)
{
	ft_free_tab(data()->env);
	data()->env = dup_env(tmp);
	if (!data()->env)
	{
		g_status = 1;
		print_error();
		return (0);
	}
	return (1);
}

static int	exec_unset(char *name)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = (char **)malloc(sizeof(char *) * ft_tabsize(data()->env));
	if (!tmp)
	{
		g_status = 1;
		print_error();
		return (0);
	}
	i = 0;
	j = 0;
	while (data()->env[i + j] && i < ft_tabsize(data()->env) - 1)
	{
		if (!strncmp(data()->env[i + j], name, ft_strlen(name)))
			j = 1;
		tmp[i] = ft_strdup(data()->env[i + j]);
		i++;
	}
	tmp[i] = NULL;
	if (!twist_tab(tmp))
		return (0);
	ft_free_tab(tmp);
	return (1);
}

static int	check_argu(t_arg *arg)
{
	char	*name;

	if (!ft_str_isalnum_eq(arg->word) || arg->word[0] == '-')
	{
		(data()->token_err) = ft_strjoin("minishell: unset: `", arg->word);
		write (2, data()->token_err, ft_strlen(data()->token_err));
		write (2, "': not a valid identifier\n", 26);
		g_status = 1;
		return (0);
	}
	name = ft_strjoin(arg->word, "=");
	if (!name)
	{
		g_status = 1;
		print_error();
		return (0);
	}
	if (exist(data()->env, name) != -1)
	{
		if (!exec_unset(name))
			return (0);
	}
	free (name);
	name = NULL;
	return (1);
}

static void	check_opt(t_arg *tmp)
{
	char	*sub;
	char	*join;

	sub = NULL;
	join = NULL;
	sub = ft_substr(tmp->next->word, 0, 2);
	join = ft_strjoin("minishell: unset: ", sub);
	data()->token_err = ft_strdup(join);
	write (2, data()->token_err, ft_strlen(data()->token_err));
	write (2, ": invalid option\n", 17);
	g_status = 2;
	ft_strclr(&join);
	ft_strclr(&sub);
}

void	unset(t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg;
	if (tmp->next && tmp->next->word[0] == '-'
		&& ft_strlen(tmp->next->word) > 1)
	{
		check_opt(tmp);
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->next && !ft_strcmp(tmp->word, "_"))
			tmp = tmp->next;
		else
		{
			if (!check_argu(tmp))
				return ;
		}
	}
	g_status = 0;
}
