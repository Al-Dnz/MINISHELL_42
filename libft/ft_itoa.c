/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:39:58 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/21 18:50:34 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_predict(long n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static long	turn_positive(long n)
{
	if (n < 0)
		return (-1 * n);
	else
		return (n);
}

char	*ft_itoa(int number)
{
	char		*str;
	int			i;
	long		n;

	n = (long)number;
	number = n < 0;
	n = turn_positive(n);
	str = malloc(sizeof(char) * (size_predict(n) + 1 + number));
	if (str == NULL)
		return (NULL);
	i = size_predict(n) + number;
	str[i--] = '\0';
	if (n == 0)
	{
		str[i] = '0';
		return (str);
	}
	while (n > 0)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	if (number)
		str[i] = '-';
	return (str);
}

char	*ft_lltoa(long long number)
{
	char		*str;
	int			i;
	long long	n;

	n = number;
	number = n < 0;
	n = turn_positive(n);
	str = malloc(sizeof(char) * (size_predict(n) + 1 + number));
	if (str == NULL)
		return (NULL);
	i = size_predict(n) + number;
	str[i--] = '\0';
	if (n == 0)
	{
		str[i] = '0';
		return (str);
	}
	while (n > 0)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	if (number)
		str[i] = '-';
	return (str);
}
