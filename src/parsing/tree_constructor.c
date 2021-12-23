#include "minishell.h"

int	set_node_init(t_btree **node)
{
	int	i;

	if (*node == NULL)
		return (0);
	i = data()->index;
	while (data()->token_tab[i] && ft_strequ(data()->token_tab[i], "|") == 0)
	{
		if (is_word(data()->token_tab[i]) == 1)
		{
			if (save_node_cmd(node, data()->token_tab[i]) == 0)
				return (0);
		}
		else if (is_redir_op(data()->token_tab[i]) == 1)
		{
			while (data()->token_tab[i] && is_redir_op(data()->token_tab[i]))
			{
				if (save_node_redir(node, data()->token_tab[i]) == 0)
					return (0);
				i++;
			}
			if (data()->token_tab[i] && is_word(data()->token_tab[i]))
			{
				if (save_node_redir_file(node, data()->token_tab[i++]) == 0)
					return (0);
			}	
		}
		if (data()->token_tab[i] && !ft_strequ(data()->token_tab[i], "|")
			&& !is_redir_op(data()->token_tab[i]))
			i++;
	}
	data()->index += i;
	return (i);
}

int	set_node(t_btree **node)
{
	int	i;

	if (*node == NULL)
		return (0);
	i = data()->index;
	while (data()->index < ft_tabsize(data()->token_tab)
		&& data()->token_tab[i] && ft_strequ(data()->token_tab[i], "|") == 0)
	{
		if (is_word(data()->token_tab[i]) == 1)
		{
			if (save_node_cmd(node, data()->token_tab[i]) == 0)
				return (0);
		}
		else if (is_redir_op(data()->token_tab[i]) == 1)
		{
			if (data()->token_tab[i] && is_redir_op(data()->token_tab[i]))
			{
				if (save_node_redir(node, data()->token_tab[i]) == 0)
					return (0);
				i++;
			}
			if (data()->token_tab[i] && is_word(data()->token_tab[i]))
			{
				if (save_node_redir_file(node, data()->token_tab[i]) == 0)
					return (0);
			}	
		}
		if (data()->token_tab[i] && !ft_strequ(data()->token_tab[i], "|")
			&& !is_redir_op(data()->token_tab[i]))
			i++;
	}
	data()->index = i;
	return (i);
}

int	tree_constructor(void)
{
	t_btree	*node;
	t_btree	*tmp;

	data()->tree = create_node(NULL, NULL);
	data()->index = 0;
	set_node(&data()->tree);
	if (data()->tree == NULL)
		return (0);
	while (data()->token_tab[data()->index]
		&& ft_strequ(data()->token_tab[data()->index], "|"))
	{
		data()->index++;
		node = create_node(NULL, NULL);
		set_node(&node);
		if (node->arg == NULL && node->redir == NULL)
		{
			free_btree(node);
			return (0);
		}
		tmp = create_node(data()->tree, node);
		if (tmp == NULL)
			return (0);
		arg_add_back(&(tmp->arg), "|");
		data()->tree = tmp;
	}
	return (1);
}
