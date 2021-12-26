#include "minishell.h"

unsigned int	g_status;

int	set_env(char **env)
{
	char	*s;

	s = NULL;
	data()->env = dup_env(env);
	if (!data()->env)
		return (0);
	s = ft_itoa(ft_atoi(getvar_val("SHLVL=", data()->env)) + 1);
	if (s == NULL)
		return (0);
	if (!change_var(data()->env, "SHLVL=", s, 0))
	{
		ft_free_tab(data()->env);
		data()->env = NULL;
		ft_strclr(&s);
		return (0);
	}
	ft_strclr(&s);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;

	g_status = 0;
	if (isatty(0) == 0)
	{
		ft_putstr_fd("open the minishell before execute commands\n", 2);
		return (EXIT_FAILURE);
	}
	if (argc > 1)
	{
		ft_putstr_fd("minishell doesn't take arguments\n", 2);
		return (EXIT_SUCCESS);
	}
	// (void)env;
	// char *path = argv[1];
	// printf("%s\n",path);
	// printf("access F_OK[%d]\n",access(path, F_OK ));
	// printf("access F_OK|R_OK[%d]\n",access(path, F_OK | R_OK ));
	// printf("access F_OK|W_OK[%d]\n",access(path, F_OK | W_OK));
	// printf("access F_OK|X_OK[%d]\n",access(path, F_OK | X_OK));
	if (!set_env(env))
		return (0);
	main_loop(env);
	return (g_status);
}

