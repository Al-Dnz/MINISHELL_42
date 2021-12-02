#include "../inc/minishell.h"

int	broken_loop(char **env)
{
	(void)env;
	return 0;
}

int main_loop(t_ms *ms, char **env)
{
	(void)env;
	char *input_message = "minishell-1.0$ ";
//	char *line;

//	line  = NULL;
	while (1)
	{
		if (ms->line)
			ft_strclr(&ms->line);
		ms->line = readline(input_message);
		if (ms->line == NULL)
			break ;
		if (!change_line(ms))
			error(ms);
		if (check_line(ms->line) && ms->line && *ms->line)
			add_history(ms->line);
		printf("[%s]\n", ms->line);
		if (!ft_strcmp(ms->line, "exit"))
		{
			ft_strclr(&ms->line);
			break;
		}
		if (ms->line)
			ft_strclr(&ms->line);
	}
	return (0);
}


int	main(int argc, char **argv, char **env)
{
	t_ms	ms;
	(void)argc;
	(void)argv;
	
	ft_bzero(&ms, sizeof(ms));
	ft_putstr_fd("hello from minishell\n", 2);
	if (argc > 2 && ft_strequ(argv[1], "-c"))
	{
		broken_loop(env);
		return (EXIT_SUCCESS);
	}
	main_loop(&ms, env);
	system("leaks minishell");
	return (EXIT_SUCCESS);
}

