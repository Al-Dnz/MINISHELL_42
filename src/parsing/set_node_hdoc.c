#include "minishell.h"


/*
t_hdoc	*set_hdoc_case_3(t_redir *redir)
{
	t_hdoc	*hdoc;

	hdoc = calloc(1, sizeof(t_hdoc));
	if (hdoc == NULL)
		return (NULL);
	hdoc->end_word = ft_strdup(redir->file);
	hdoc->next = NULL;
	return (hdoc);
}
*/

int	set_tree_hdoc(t_btree **tree)
{
	if ((*tree)->left != NULL)
		set_tree_hdoc(&(*tree)->left);
	if ((*tree)->right != NULL)
		set_tree_hdoc(&(*tree)->right);
	if (tree != NULL)
	{
		//if fork_hdoc_readline == 1
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
	// return (1);
}