/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:02:31 by ivloisy           #+#    #+#             */
/*   Updated: 2021/12/14 19:43:33 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_arg *arg)
{
/* 	char	*pwd;
	
	pwd = NULL;
	pwd = getcwd(pwd, 0); */
	(void)arg;
	ft_putnbr_fd(chdir("/Users/ivloisy"), 1);
	ft_putchar_fd('\n', 1);
}