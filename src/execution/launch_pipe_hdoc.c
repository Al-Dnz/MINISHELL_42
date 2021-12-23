#include "minishell.h"

int	launch_pipe_hdoc(t_btree *tree)
{
	if (tree->left != NULL)
		launch_pipe_hdoc(tree->left);
	if (tree->right != NULL)
		launch_pipe_hdoc(tree->right);
	if (tree != NULL)
	{
		if (hdoc_pipe(tree) == 1)
			data()->stop = 1;
	}
	return (1);
}
