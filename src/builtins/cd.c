/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:02:31 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/25 23:05:00 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static char	*set_path(t_arg *arg)
{
	char	*path;

	if (arg->next && !ft_strncmp(arg->next->word, "//", 2)
			&& (!arg->next->word[2] || arg->next->word[2] != '/'))
		data()->dd = 1;
	if (!arg->next || (arg->next->word[0] == '/' && arg->next->word[1]
		&& arg->next->word[1] != '/')
		|| !ft_strncmp(arg->next->word, "///", 3) || arg->next->word[0] == '~')
		data()->dd = 0;
	if (!arg->next || !ft_strcmp(arg->next->word, "~"))
		path = ft_strdup(getvar_val("HOME=", data()->env));
	else if (!strcmp(arg->next->word, "-"))
	{
		if (!ft_strncmp(getvar_val("OLDPWD=", data()->env), "//", 2))
			data()->dd = 1;
		else
			data()->dd = 0;
		path = ft_strdup(getvar_val("OLDPWD=", data()->env));
		data()->dash = 1;
	}
	else
		path = ft_strdup(arg->next->word);
	return (path);
}

static void	print_opt_error(char *opt)
{
	write(2, "minishell: cd: ", 15);
	write(2, opt, ft_strlen(opt));
	write(2, ": invalid option\n", 17);
}

static void	update_pwd(void)
{
	if (!change_var(data()->env, "OLDPWD=",
			getvar_val("PWD=", data()->env), 0))
	{
		g_status = 1;
		data()->token_err = ft_strdup("minishell");
		print_error();
	}
	else
	{
		pwd(data()->dash);
		g_status = 0;
	}
}

static void	exec_cd(char *path)
{
	int		err;

	if (path[0] == '-' && ft_strlen(path) > 1)
	{
		print_opt_error(path);
		g_status = 1;
		ft_strclr(&path);
		return ;
	}
	err = chdir(path);
	if (err == -1)
	{
		data()->token_err = ft_strjoin("minishell: cd: ", path);
		g_status = 1;
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
		g_status = 1;
		write(2, "minishell: cd: too many arguments\n", 34);
		return ;
	}
	path = set_path(arg);
	if (path)
		exec_cd(path);
	else
	{
		g_status = 1;
		data()->token_err = ft_strdup("minishell");
		print_error();
	}
}
