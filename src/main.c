#include "../inc/minishell.h"

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
			add_history(line);
		printf("[%s]\n", line);
		if (line)
			ft_strclr(&line);
	}
	return (0);
}


int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	
	ft_putstr_fd("hello from minishell\n", 2);
	if (argc > 2 && ft_strequ(argv[1], "-c"))
	{
		broken_loop(env);
		return (EXIT_SUCCESS);
	}
	main_loop(env);
	return (EXIT_SUCCESS);
}

