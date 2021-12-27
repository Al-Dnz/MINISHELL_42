#include "minishell.h"

void	clean_program(void)
{
	ft_free_tab(g_data.token_tab);
	g_data.token_tab = NULL;
	ft_free_tab(g_data.env);
	g_data.env = NULL;
	free_btree(g_data.tree);
	g_data.tree = NULL;
	ft_strclr(&g_data.str);
	if (g_data.token_err)
		ft_strclr(&g_data.token_err);
	g_data.str = NULL;
}

void	clean_process(void)
{
	ft_free_tab(g_data.token_tab);
	g_data.token_tab = NULL;
	free_btree(g_data.tree);
	g_data.tree = NULL;
	ft_strclr(&g_data.str);
	if (g_data.token_err)
		ft_strclr(&g_data.token_err);
	g_data.str = NULL;
}
