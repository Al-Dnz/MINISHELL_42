#include "minishell.h"

t_btree	*create_node(t_btree *left, t_btree *right)
{
	t_btree	*node;

	node = malloc(sizeof(t_btree));
	if (node == NULL)
		return (NULL);
	node->left = left;
	node->right = right;
	node->arg = NULL;
	node->redir = NULL;
	node->hdoc = NULL;
	return (node);
}

int	free_btree(t_btree *node, int ret)
{
	if (node != NULL)
	{
		if (node->left != NULL)
			free_btree(node->left, 0);
		if (node->right != NULL)
			free_btree(node->right, 0);
		
		arg_clr(&(node->arg));
		redir_clr(&(node->redir));
		// if (node->hdoc != NULL)
		// 	free_hdoc_node(node->hdoc);
		// 
		free(node);
	}
	return (ret);
}