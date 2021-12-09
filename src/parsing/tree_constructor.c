#include "minishell.h"

int	save_node_cmd(t_btree *node, char *str)
{
	char	*tmp;

	tmp = NULL;//ft_replace_token(str);
	if (tmp == NULL)
		return (1);
	if (arg_add_back(&(node->arg), str) == 0)
		return (1);
	return (0);
}

int	save_node_redir(t_btree *node, char *str)
{
	if (redir_add_back(&(node->redir), str) == 0)
		return (1);
	return (0);
}

int save_node_redir_file(t_btree *node, char *str)
{
	t_redir *redir;

	redir = node->redir;
	if (redir == NULL)
		return (0);
	while (redir->next)
		redir = redir->next;
	redir->file = ft_strdup(str);
	if (redir->file == NULL)
		return (0);
	return (1);
}

int	set_node(t_btree *node)
{
	int	i;

	node = create_node(NULL, NULL);
	if (node == NULL)
		return (0);
	i = 0;
	while (g_data.token_tab[i] && !ft_strequ(g_data.token_tab[i], "|"))
	{
		if (is_word(g_data.token_tab[i]) == 1)
		{
			if(save_node_cmd(node, g_data.token_tab[i]) == 0)
				return (0);
		}
		else if (is_redir_op( g_data.token_tab[i]) == 1)
		{
			// maybe a loop could be better here ??
			if (g_data.token_tab[i] && is_redir_op(g_data.token_tab[i]))
				if (save_node_redir(node, g_data.token_tab[i++]) == 0)
					return (0);
			if (g_data.token_tab[i] && is_word(g_data.token_tab[i]))
				if(save_node_redir_file(node, g_data.token_tab[i]) == 0)
					return (0);	
		}
		if (g_data.token_tab[i] && !ft_strequ(g_data.token_tab[i], "|")
			&& !is_redir_op(g_data.token_tab[i]))
			i++;
	}
	 g_data.token_tab += i;
	return (1);
}