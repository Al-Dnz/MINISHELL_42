#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' );
}

int	is_pipe_op(char c)
{
	return (c == '|');
}

int	is_redir_op(char *str)
{
	return (ft_strequ(str, ">") || ft_strequ(str, "<") || ft_strequ(str, ">>")
		|| ft_strequ(str, "<<"));
}

int	is_word(char *str)
{
	if (str == NULL || is_redir_op(str) == 1 || ft_strequ(str, "|"))
		return (0);
	return (1);
}
