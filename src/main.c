#include "minishell.h"

t_data	g_data;

static int	set_env(char **env)
{
	char	*s;
	char	**envbis;
	
	s = NULL;
	envbis = dup_env(env);
//	g_data.env = env;
	if (envbis == NULL)
		return (0);
	s = ft_itoa(ft_atoi(getvar_val("SHLVL=", envbis)) + 1);
	if (!s)
		return (0);
	change_var(envbis, "SHLVL=", s);
	g_data.env = envbis;
	if (!g_data.env)
	{
		ft_strclr(&s);
//		ft_free_tab(envbis);
		return (0);
	}
//	ft_free_tab(envbis);
	ft_strclr(&s);
	ft_print_tab2(g_data.env);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	
//	ft_bzero(&g_data, sizeof(g_data));

	if (!set_env(env))
		return (0);
	ft_free_tab(g_data.env);
	return (0);
/* 
	ft_putstr_fd("hello from minishell\n", 2);
	if (argc > 2 && ft_strequ(argv[1], "-c"))
	{
		return (EXIT_SUCCESS);
	}
//	main_loop(env);
	return (g_data.status); */
}

