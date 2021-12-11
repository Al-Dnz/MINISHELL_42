#include "minishell.h"

void	display_arg(t_arg *arg)
{
	printf("arg: ");
	while (arg != NULL)
	{
		printf("[%s]->", arg->word);
		arg = arg->next;
	}
	printf("NULL\n");
}

void	display_redir(t_redir *redir)
{
	static char *sym_arr[6] = {"-1", "<", ">", "<<", ">>", 0};

	printf("redir: ");
	while (redir)
	{
		printf("[%s|%s]->",sym_arr[redir->kind], redir->file);
		redir = redir->next;
	}
	printf("NULL\n");
}

void display_tree(t_btree *node)
{
	static int i;

	printf("(%d)--------------------------------------------\n", i++);
	if (node == NULL)
	{
		printf("NULL\n");
		return ;
	}
	display_redir(node->redir);
	display_arg(node->arg);
	display_tree(node->left);
	display_tree(node->right);
}