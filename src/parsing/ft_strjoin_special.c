#include "minishell.h"

char	*ft_strjoin_special(char *s1, char *s2, int nb)
{
	char	*str;
	char	*to_free1;
	char	*to_free2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s1));
	else if (s2 == NULL)
		return (ft_strdup(s2));
	to_free1 = s1;
	to_free2 = s2;
	str = ft_strjoin(s1, s2);
	if (str == NULL)
		return (NULL);
	if (*to_free1 && (nb == 0 || nb == 2) && nb != -1)
		free(to_free1);
	if (*to_free2 && (nb == 1 || nb == 2) && nb != -1)
		free(to_free2);
	return (str);
}

char	*revert_null_str(char *dest, char *src)
{
	dest = ft_strdup(src);
	ft_strclr(&src);
	return (dest);
}

void	ft_free_null(char **str1, char **str2, int mode)
{
	if (*str1 && (mode == 0 || mode == 2) && mode != -1)
		ft_strclr(str1);
	if (*str2 && (mode == 1 || mode == 2) && mode != -1)
		ft_strclr(str2);

}

char	*ft_strjoin_special_2(char **s1, char **s2, int nb)
{
	char	*str;
	char	**to_free1;
	char	**to_free2;

	if (*s1 == NULL && s2 == NULL)
		return (NULL);
	else if (*s1 == NULL)
		return (revert_null_str(*s1, *s2));
	else if (*s2 == NULL)
		return (revert_null_str(*s2, *s1));
	to_free1 = s1;
	to_free2 = s2;
	str = ft_strjoin(*s1, *s2);
	if (str == NULL)
		return (NULL);
	ft_free_null(to_free1, to_free2, nb);
	return (str);
}

