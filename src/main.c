#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	
	ft_bzero(&g_data, sizeof(g_data));
	ft_putstr_fd("hello from minishell\n", 2);
	if (argc > 2 && ft_strequ(argv[1], "-c"))
	{
		return (EXIT_SUCCESS);
	}
	main_loop(env);
	return (g_data.status);
}

