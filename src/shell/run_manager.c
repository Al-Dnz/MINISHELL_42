#include "minishell.h"

void	init_g_data(void)
{
	g_data.chd_status = 0;
	g_data.child_pid = 0;
	g_data.status = 0;
	g_data.quit = 0;
	g_data.index = 0;
	g_data.in_hdoc = 0;
	g_data.displayer = 0;
	g_data.str = NULL;
	g_data.token_tab = NULL;
	g_data.tree = NULL;
}

void	reinit_g_data(void)
{
	// g_data.chd_status = 0;
	// g_data.child_pid = 0;
	g_data.quit = 0;
	g_data.index = 0;
	g_data.in_hdoc = 0;
	g_data.displayer = 0;
	ft_free_tab(g_data.token_tab);
	g_data.token_tab = NULL;
	free_btree(g_data.tree);
	g_data.tree = NULL;
	ft_strclr(&g_data.str);
	g_data.str = NULL;
}

void	main_loop(char **env)
{
	static char	*input_message = "minishell-1.0$ ";
	char		*line;

	if (isatty(0) == 0)
		return ;
	ft_signal();
	line = NULL;
	init_g_data();
	while (1)
	{
		if (line)
			ft_strclr(&line);
		line = readline(input_message);
		if (line == NULL)
			exit_by_signal();
		if (line && *line)
		{
			add_history(line);
			if (!check_syntax(line))
				print_error();
			else
				run(line, env);
		}
		if (line)
			ft_strclr(&line);
	}
}

void	run(char *line, char **env)
{
	int	std_out;
	int	std_in;

	(void)env;
	if (get_all_token(line) == 0)
		return ;
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	tree_constructor();
	set_arg_tab(&g_data.tree);
	set_tree_hdoc(&g_data.tree);
	if (valid_redir(g_data.tree) == 0)
		return ;
	launch_tree(g_data.tree);
	dup2(std_out, STDOUT_FILENO);
	dup2(std_in, STDIN_FILENO);
	reinit_g_data();
}
