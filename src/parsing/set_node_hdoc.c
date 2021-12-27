#include "minishell.h"

int	set_tree_hdoc(t_btree **tree)
{
	if ((*tree)->left != NULL)
		set_tree_hdoc(&(*tree)->left);
	if ((*tree)->right != NULL)
		set_tree_hdoc(&(*tree)->right);
	if (tree != NULL)
	{
		if (set_node_hdoc(tree) == 1)
			g_data.stop = 1;
	}
	return (1);
}

int	set_node_hdoc(t_btree **node)
{
	t_redir	*tmp;

	tmp = (*node)->redir;
	while (tmp != NULL)
	{
		if (tmp->kind == 3)
			hdoc_add_back(&((*node)->hdoc), tmp->file);
		tmp = tmp->next;
	}
	return (hdoc_pipe(*node));
}
