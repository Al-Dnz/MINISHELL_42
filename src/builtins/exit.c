/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:17:20 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/26 11:51:41 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_num(char *str)
{
	data()->token_err = ft_strdup(str);
	g_status = 255;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(data()->token_err, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	if (isatty(0))///A VOIR SI CA FOUT PAS LA MERDE
	{
		clean_program();
		exit(g_status);
	}
}

static int	ft_can_int_convert(char *str)
{
	long long	atoll_res;
	char		*lltoa_res;

	atoll_res = ft_atolong(str);
	lltoa_res = ft_lltoa(atoll_res);
	if (ft_strcmp(lltoa_res, str) == 0 || (ft_strcmp(lltoa_res, str + 1) == 0
			&& str[0] == '+'))
	{
		free(lltoa_res);
		return (1);
	}
	free(lltoa_res);
	return (0);
}

int	str_is_num(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == 0)
		return (1);
	while (*str)
	{
		if (ft_isdigit(*str++) == 0)
			return (1);
	}
	return (0);
}

static void	check_exit(t_arg *arg, int i)
{
	if (i > 1)
	{
		if ((i > 2 && str_is_num(arg->next->word))
			|| str_is_num(arg->next->word))
			err_num(arg->next->word);
		else if (i > 2 && !str_is_num(arg->next->word))
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_status = 1;
		}
		else if (i == 2 && !str_is_num(arg->next->word))
		{
			if (ft_can_int_convert(arg->next->word))
			{
				g_status = (unsigned char)ft_atolong(arg->next->word);
				clean_exit(g_status, 0);
			}
			else
				err_num(arg->next->word);
		}
	}
	else
		clean_exit(g_status, 0);
}

void	cmd_exit(t_arg *arg)
{
	int		i;
	t_arg	*tmp;

	i = 1;
	tmp = arg;
	if (isatty(0))
		write(1, "exit\n", 5);
	while (tmp ->next)
	{
		tmp = tmp->next;
		i++;
	}
	check_exit(arg, i);
}
