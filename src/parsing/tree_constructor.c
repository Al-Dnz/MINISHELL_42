#include "minishell.h"

int	save_node_cmd(t_btree **node, char *str)
{
	char	*new_str;

	new_str = token_cleaner(str);
	if (new_str == NULL)
		return (0);
	if (arg_add_back(&(*node)->arg, new_str) == 0)
		return (0);
	return (1);
}

int	save_node_redir(t_btree **node, char *str)
{
	if (redir_add_back(&(*node)->redir, str) == 0)
		return (0);
	return (1);
}

int save_node_redir_file(t_btree **node, char *str)
{
	t_redir	*redir;
	t_redir	*tmp;
	char	*new_str;

	redir = (*node)->redir;
	if (redir == NULL)
		return (0);
	tmp = ft_redirlast(redir);
	new_str = token_cleaner(str);
	if (new_str == NULL)
		return (0);
	tmp->file = ft_strdup(new_str);
	if (tmp->file == NULL)
		return (0);
	return (1);
}

int	set_node_init(t_btree **node)
{
	int	i;

	if (*node == NULL)
		return (0);
	i = g_data.index;
	while (g_data.token_tab[i] && ft_strequ(g_data.token_tab[i], "|") == 0)
	{
		if (is_word(g_data.token_tab[i]) == 1)
		{
			if(save_node_cmd(node, g_data.token_tab[i]) == 0)
				return (0);
		}
		else if (is_redir_op(g_data.token_tab[i]) == 1)
		{
			// maybe a condition could be better here ??
			while (g_data.token_tab[i] && is_redir_op(g_data.token_tab[i]))
			{
				if(save_node_redir(node, g_data.token_tab[i]) == 0)
					return (0);
				i++;
			}
			if (g_data.token_tab[i] && is_word(g_data.token_tab[i]))
			{
				if(save_node_redir_file(node, g_data.token_tab[i++]) == 0)
					return (0);	
			}	
		}
		if (g_data.token_tab[i] && !ft_strequ(g_data.token_tab[i], "|")
			&& !is_redir_op(g_data.token_tab[i]))
			i++;
	}
	g_data.index += i;
	return (i);
}


int	set_node(t_btree **node)
{
	int	i;

	if (*node == NULL)
		return (0);
	i = g_data.index;
	// printf("=>begin{%d}\n", g_data.index);
	while (g_data.index <  ft_tabsize(g_data.token_tab) && g_data.token_tab[i] && ft_strequ(g_data.token_tab[i], "|") == 0)
	{
		if (is_word(g_data.token_tab[i]) == 1)
		{
			if(save_node_cmd(node, g_data.token_tab[i]) == 0)
				return (0);
		}
		else if (is_redir_op(g_data.token_tab[i]) == 1)
		{
			// maybe a condition could be better here ??
			if (g_data.token_tab[i] && is_redir_op(g_data.token_tab[i]))
			{
				if(save_node_redir(node, g_data.token_tab[i]) == 0)
					return (0);
				i++;
			}
			if (g_data.token_tab[i] && is_word(g_data.token_tab[i]))
			{
				if(save_node_redir_file(node, g_data.token_tab[i]) == 0)
					return (0);	
			}	
		}
		if (g_data.token_tab[i] && !ft_strequ(g_data.token_tab[i], "|")
			&& !is_redir_op(g_data.token_tab[i]))
			i++;
	}
	g_data.index = i;
	// printf("=>end{%d}\n", g_data.index);
	return (i);
}

int	tree_constructor(void)
{
	t_btree	*node;
	t_btree	*tmp;
	
	g_data.tree = create_node(NULL, NULL);
	g_data.index = 0;
	set_node(&g_data.tree);
	if (g_data.tree  == NULL)
		return (0);
	while (g_data.token_tab[g_data.index] && ft_strequ(g_data.token_tab[g_data.index], "|"))
	{
		g_data.index++;
		node = create_node(NULL, NULL);
		set_node(&node);
		if (node->arg == NULL && node->redir == NULL)
		{
			free_btree(node);
			//insert a error solution here
			return (0);
		}
		tmp = create_node(g_data.tree, node);
		if (tmp == NULL)
			return (0);
		arg_add_back(&(tmp->arg), "|");
		g_data.tree = tmp;
	}
	return (1);
}