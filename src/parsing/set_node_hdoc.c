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
		//if fork_rdl_hdoc == 1
		if (set_node_hdoc(tree) == 1)
			g_data.stop = 1;
	}
	return (1);
}

int	set_node_hdoc(t_btree **node)
{
	t_redir	*tmp;
	//t_hdoc	*current;

	tmp = (*node)->redir;
	while (tmp != NULL)
	{
		if (tmp->kind == 3)
		{

			hdoc_add_back(&((*node)->hdoc), tmp->file);
			// if (node->hdoc == NULL)
			// 	node->hdoc = set_hdoc_case_3(tmp);
			// else
			// {
			// 	current = node->hdoc;
			// 	while (current->next != NULL)
			// 		current = current->next;
			// 	current->next = set_hdoc_case_3(tmp);
			// }
		}
		tmp = tmp->next;
	}
	return (fork_rdl_hdoc(*node));
	// return (1);
}