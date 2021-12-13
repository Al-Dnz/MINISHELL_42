#include "minishell.h"

char	*ft_strjoin_special(char *s1, char *s2, int mode)
{
	char	*str;
	char	*freeable_1;
	char	*freeable_2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s1));
	else if (s2 == NULL)
		return (ft_strdup(s2));
	freeable_1 = s1;
	freeable_2 = s2;
	str = ft_strjoin(s1, s2);
	if (str == NULL)
		return (NULL);
	if (*freeable_1 && (mode == 0 || mode == 2) && mode != -1)
		free(freeable_1);
	if (*freeable_2 && (mode == 1 || mode == 2) && mode != -1)
		free(freeable_2);
	return (str);
}

char	*ft_strjoin_special_2(char **s1, char **s2, int mode)
{
	char	*str;
	char	**freeable_1;
	char	**freeable_2;

	if (*s1 == NULL && s2 == NULL)
		return (NULL);
	else if (*s1 == NULL)
		return (revert_null_str(*s1, *s2));
	else if (*s2 == NULL)
		return (revert_null_str(*s2, *s1));
	freeable_1 = s1;
	freeable_2 = s2;
	str = ft_strjoin(*s1, *s2);
	if (str == NULL)
		return (NULL);
	free_mode(freeable_1, freeable_2, mode);
	return (str);
}

char	*revert_null_str(char *dest, char *src)
{
	dest = ft_strdup(src);
	ft_strclr(&src);
	return (dest);
}

void	free_mode(char **str1, char **str2, int mode)
{
	if (*str1 && (mode == 0 || mode == 2) && mode != -1)
		ft_strclr(str1);
	if (*str2 && (mode == 1 || mode == 2) && mode != -1)
		ft_strclr(str2);
}