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
		printf("[%s|%s]->", sym_arr[redir->kind], redir->file);
		redir = redir->next;
	}
	printf("NULL\n");
}

void display_tree(t_btree *node)
{
	static int i;

	if (g_data.displayer == 0)
		i = 0;
	g_data.displayer = 1;
	printf("(%d)--------------------------------------------\n", i++);
	if (node == NULL)
	{
		printf("NULL\n");
		return ;
	}
	display_redir(node->redir);
	display_arg(node->arg);
	ft_putstr_fd("arr: ", 1);
	ft_print_tab(node->arr);
	ft_putstr_fd("\n", 1);
	display_tree(node->right);
	display_tree(node->left);
}