#include "minishell.h"

int	count_token(char *line)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != '\n')
	{
		len = token_size(line + i);
		if (len > 0)
		{
			count++;
			i += len;
		}
		else
			return (-1);
		while (line[i] == ' ')
			i++;
	}
	return (count);
}

char	**create_token_tab(int size)
{
	char **tab;

	if (size == -1)
		return (NULL);
	tab = malloc(sizeof(char *) * (size + 1));
	if (tab == NULL)
		return (NULL);
	tab[size] = NULL;		 
	return (tab);
}

int	get_all_token(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	g_data.token_tab = create_token_tab(count_token(line));
	if (g_data.token_tab == NULL)
		return (1);
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (token_size(line + i) > 0)
		{
			(g_data.token_tab[j]) = ft_substr(line, i, token_size(line + i));
			if (g_data.token_tab[j] == NULL)
			{
				ft_retro_free_tab(g_data.token_tab);
				return (0);
			}
			j++;
			i += token_size(line + i);
		}
		else
		{
			ft_retro_free_tab(g_data.token_tab);
			return (0);
		}
		while (line[i] == ' ')
			i++;
	}
	return (1);
}
