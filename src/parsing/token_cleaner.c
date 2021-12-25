#include "minishell.h"

char	*get_exp(char **str)
{
	int		len;
	char	*dest;
	char	*var_name;
	char	*var_eq;

	len = 0;
	(*str)++;
	if (**str == 0)
		return (ft_strdup("$"));
	else if (is_quote(**str))
		return (ft_strdup(""));
	else if (**str == '?')
	{
		(*str)++;
		return (ft_itoa(g_status));
	}
	while ((*str)[len] && (*str)[len] != ' ' && !is_quote((*str)[len])
		&& (*str)[len] != '$')
		len++;
	var_name = ft_substr(*str, 0, len);
	*str += len;
	var_eq = ft_strjoin(var_name, "=");
	dest = ft_strdup(getvar_val(var_eq, data()->env));
	ft_strclr(&var_eq);
	ft_strclr(&var_name);
	return (dest);
}

char	*ft_replace_str(char *str)
{	
	char	*dest;
	char	*tmp;
	int		i;

	dest = NULL;
	i = 0;
	while (*str)
	{
		if (*str == '$')
			tmp = get_exp(&str);
		else
		{
			i = 0;
			while (str[i] && str[i] != '$')
				i++;
			tmp = ft_substr(str, 0, i);
			str += i;
		}
		dest = ft_strextend_2(&dest, &tmp, 2);
	}
	return (dest);
}

char	*store_exp_unq(char **str, char type)
{
	int		len;
	char	*dest;
	char	*tmp;

	len = 0;
	dest = NULL;
	tmp = NULL;
	if (type == '\'' || type == '\"')
		len = quoted_string_size(*str, type);
	else if (type == 0)
		len = unquoted_string_size(*str);
	if (type == '\'')
		dest = ft_substr(*str + 1, 0, len - 2);
	else if (type == '\"')
		tmp = ft_substr(*str + 1, 0, len - 2);
	else if (type == 0)
		tmp = ft_substr(*str, 0, len);
	if (type == 0 || type == '\"')
		dest = ft_replace_str(tmp);
	if (tmp != NULL)
		free(tmp);
	*str += len;
	return (dest);
}

char	*store_dollar(char **str)
{
	char	*tmp;

	tmp = NULL;
	if ((*str)[1] == 0 || (*str)[1] == ' '
		|| (*str)[1] == '|')
	{
		(*str)++;
		tmp = ft_strdup("$");
	}
	else if ((*str)[1] == '$')
	{
		(*str) += 2;
		tmp = ft_strdup("");
	}
	else if (is_quote((*str)[1]))
	{
		(*str)++;
		tmp = ft_strdup("");
	}
	else
		tmp = store_exp_unq(str, 0);
	return (tmp);
}

/*
	Return the token entirely unquoted and expanded
*/
char	*token_cleaner(char *str)
{
	char	*tmp;
	char	*dest;
	int		i;

	i = 0;
	dest = NULL;
	while (*str)
	{
		if (*str == '\'')
			tmp = store_exp_unq(&str, '\'');
		else if (*str == '\"')
			tmp = store_exp_unq(&str, '\"');
		else if (*str == '$')
			tmp = store_dollar(&str);
		else
			tmp = store_exp_unq(&str, 0);
		dest = ft_strextend_2(&dest, &tmp, 2);
		if (dest == NULL)
			return (NULL);
	}
	return (dest);
}
