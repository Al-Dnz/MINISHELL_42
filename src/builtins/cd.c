/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:02:31 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/27 20:45:47 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_dash(char **path)
{
	if (exist(g_data.env, "OLDPWD=") != -1)
	{
		if (!ft_strncmp(getvar_val("OLDPWD=", g_data.env), "//", 2))
			g_data.dd = 1;
		else
			g_data.dd = 0;
		*path = ft_strdup(getvar_val("OLDPWD=", g_data.env));
		g_data.dash = 1;
	}
	else
		print_err_env("OLDPWD");
}

static char	*set_path(t_arg *arg)
{
	char	*path;

	path = NULL;
	if (arg->next && !ft_strncmp(arg->next->word, "//", 2)
		&& (!arg->next->word[2] || arg->next->word[2] != '/'))
		g_data.dd = 1;
	if (!arg->next || (arg->next->word[0] == '/' && arg->next->word[1]
			&& arg->next->word[1] != '/')
		|| !ft_strncmp(arg->next->word, "///", 3) || arg->next->word[0] == '~')
		g_data.dd = 0;
	if (!arg->next || !ft_strcmp(arg->next->word, "~"))
	{
		if (exist(g_data.env, "HOME=") != -1)
			path = ft_strdup(getvar_val("HOME=", g_data.env));
		else
			print_err_env("HOME");
	}
	else if (!strcmp(arg->next->word, "-"))
		set_dash(&path);
	else
		path = ft_strdup(arg->next->word);
	return (path);
}

static void	update_pwd(void)
{
	if (exist(g_data.env, "OLDPWD=") != -1)
	{
		if (exist(g_data.env, "PWD=") != -1)
		{
			if (!change_var(g_data.env, "OLDPWD=",
					getvar_val("PWD=", g_data.env), 0))
			{
				g_data.status = 1;
				g_data.token_err = ft_strdup("minishell");
				print_error();
			}
			else
			{
				pwd(g_data.dash);
				g_data.status = 0;
			}
		}
	}
	else
	{
		pwd(g_data.dash);
		g_data.status = 0;
	}
}

static void	exec_cd(char *path)
{
	int		err;

	if (path[0] == '-' && ft_strlen(path) > 1)
	{
		print_opt_error(path);
		g_data.status = 1;
		ft_strclr(&path);
		return ;
	}
	err = chdir(path);
	if (err == -1)
	{
		g_data.token_err = ft_strjoin("minishell: cd: ", path);
		g_data.status = 1;
		print_error();
	}
	else
	{
		update_pwd();
	}
	ft_strclr(&path);
}

void	cd(t_arg *arg)
{
	char	*path;

	if (arg->next && arg->next->next)
	{
		g_data.status = 1;
		write(2, "minishell: cd: too many arguments\n", 34);
		return ;
	}
	path = set_path(arg);
	if (path)
		exec_cd(path);
	else
	{
		g_data.status = 1;
		g_data.token_err = ft_strdup("minishell");
		print_error();
	}
}
