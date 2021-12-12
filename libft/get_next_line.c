/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:57:12 by adenhez           #+#    #+#             */
/*   Updated: 2021/06/09 13:28:28 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	g_byte;

int	gnl_process(char **str, char **line)
{
	char	*temp;
	char	*ptr;
	int		len;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len] != 0)
		len++;
	ptr = ft_strchr(*str, '\n');
	if (ptr != NULL)
	{
		*line = ft_strsub(*str, 0, len);
		temp = ft_strdup(++ptr);
		if (temp == NULL)
			return (-1);
		free(*str);
		*str = temp;
	}
	else
	{
		*line = ft_strdup(*str);
		if (*line == NULL)
			return (-1);
		ft_strclr(str);
	}
	return (1);
}

int	output(int byte, char **str, char **line)
{
	if (byte < 0)
		return (-1);
	else if (byte == 0 && *str == NULL)
	{
		*line = ft_strdup("");
		if (*line == NULL)
			return (-1);
		return (0);
	}
	else
	{
		if (gnl_process(&(*str), line) == -1)
			return (-1);
		if (*str == NULL)
			return (0);
		return (1);
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*str;
	char		*temp;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	g_byte = read(fd, buf, BUFFER_SIZE);
	while (g_byte > 0)
	{
		buf[g_byte] = 0;
		if (str == NULL)
			str = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(str, buf);
			if (temp == NULL)
				return (-1);
			str = temp;
		}
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (g_byte < 0)
		return (-1);
	return (output(g_byte, &str, line));
}
