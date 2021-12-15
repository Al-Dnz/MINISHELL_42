#include "minishell.h"

int	broken_loop(char **env)
{
	(void)env;
	return 0;
}

int main_loop(char **env)
{
	(void)env;
	char *input_message = "minishell-1.0$ ";
	char *line;

	line  = NULL;
	while (1)
	{
		if (line)
			ft_strclr(&line);
		line = readline(input_message);
		if (line == NULL)
			break ;
		if (line && *line)
		{
			add_history(line);
			if (!check_syntax(line))
				print_error();//////
			else
				run(line, env);
		}
		// printf("[%s]\n", line);
		if (line)
			ft_strclr(&line);
	}
	return (0);
}

static int	set_env(char **env)
{
	g_data.env = dup_env(env);
	if (!g_data.env)
		return (0);
	
	g_data.env = change_var(env, "SHLVL=", ft_itoa(ft_atoi(getvar_val("SHLVL=", g_data.env)) + 1));
	if (!g_data.env)
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
//	(void)env;

/* 	t_arg *arg;
	arg = malloc(sizeof(t_arg));
	arg->word = "coucou";
	arg->next = NULL; */
	
	ft_bzero(&g_data, sizeof(g_data));


	if (!set_env(env))
		return (0);

//	printf("/////[%s]\n", getvar_val("HOME=", g_data.env));
//	ft_print_tab2(g_data.env);
 /*
	cd(arg);
	ft_print_tab2(env);
 */
	ft_putstr_fd("hello from minishell\n", 2);
	if (argc > 2 && ft_strequ(argv[1], "-c"))
	{
		broken_loop(env);
		return (EXIT_SUCCESS);
	}
	main_loop(env);
	// char *line;
	// char **tab;

	// while (1)
	// {
	// 	line = readline("> ");
	// 	tab = ft_special_split(line, '|');
	// 	ft_print_tab2(tab);
	// 	write(1, "\n", 1);
	// 	ft_free_tab(tab);
	// }
	return (EXIT_SUCCESS);
}

