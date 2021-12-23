#include "minishell.h"

t_data	g_data;

static int	set_env(char **env)
{
	data()->env = dup_env(env);
	if (!data()->env)
		return (0);
	
	data()->env = change_var(env, "SHLVL=", ft_itoa(ft_atoi(getvar_val("SHLVL=", data()->env)) + 1));
	if (!data()->env)
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
	return (g_status);
}

