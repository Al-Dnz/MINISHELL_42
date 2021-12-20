#include "minishell.h"


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
	
	ft_bzero(&g_data, sizeof(g_data));

	if (!set_env(env))
		return (0);

	ft_putstr_fd("hello from minishell\n", 2);
	if (argc > 2 && ft_strequ(argv[1], "-c"))
	{
		return (EXIT_SUCCESS);
	}
	main_loop(env);
	return (g_data.status);
}

