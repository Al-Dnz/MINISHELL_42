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
	node->arr = NULL;
	node->redir = NULL;
	node->hdoc = NULL;
	return (node);
}

int	free_btree(t_btree *node)
{
	if (node == NULL)
		return (1);
	if (node->left != NULL)
		free_btree(node->left);
	if (node->right != NULL)
		free_btree(node->right);
	if (node->arg != NULL)
	{
		arg_clr(&(node->arg));
		free(node->arg);
		node->arg = NULL;
	}
	if (node->redir != NULL)
	{
		redir_clr(&(node->redir));
		node->redir = NULL;
	}
	if (node->hdoc != NULL)
	{
		hdoc_clr(&(node->hdoc));
		node->hdoc = NULL;
	}
	ft_free_tab(node->arr);
	free(node);
	node = NULL;
	return (1);
}
