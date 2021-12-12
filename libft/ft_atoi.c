/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:30:28 by adenhez           #+#    #+#             */
/*   Updated: 2021/06/09 12:44:20 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	long int	res;
	int			i;
	long int	sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + str[i] - '0';
		if (res > 2147483647 && ft_isdigit(str[i + 1]) && sign > 0)
			return (-1);
		else if (res > 2147483648 && ft_isdigit(str[i + 1]) && sign < 0)
			return (0);
		i++;
	}
	return (res * sign);
}

long	ft_atoi_special(const char *str)
{
	long int	res;
	int			i;
	long int	sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		res = res * 10 + str[i] - '0';
		if (res > 2147483647 && ft_isdigit(str[i + 1]) && sign > 0)
			return (-1);
		i++;
	}
	return (res * sign);
}

int	ft_atoi_checker(const char *str)
{
	long int	res;
	int			i;
	int			digit_checker;

	res = 0;
	i = 0;
	digit_checker = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (ft_isdigit(str[i]))
			digit_checker = 1;
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (!digit_checker)
		return (0);
	return (1);
}

long long	ft_atolong(const char *str)
{
	long long	res;
	int			i;
	long int	sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
