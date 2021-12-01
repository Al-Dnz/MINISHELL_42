#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	ft_putstr_fd("hello from minishell", 2);
	return (EXIT_SUCCESS);
}

