#include "minishell.h"

unsigned int	g_status;

static int	set_env(char **env)
{
	char	*s;
	char	**tmp;

	s = NULL;
//	data()->env = dup_env(env);
	tmp = dup_env(env);
	if (tmp == NULL)
		return (0);
	s = ft_itoa(ft_atoi(getvar_val("SHLVL=", tmp)) + 1);
	if (s == NULL)
	{
		ft_free_tab(tmp);
		return (0);
	}
	data()->env = change_var(tmp, "SHLVL=", s);
	if (!data()->env)
	{
		ft_strclr(&s);
		ft_free_tab(tmp);
		return (0);
	}
	ft_free_tab(tmp);
	ft_strclr(&s);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	
//	ft_bzero(&g_data, sizeof(g_data));

	if (!set_env(env))
		return (0);
	ft_print_tab(data()->env);
/* 	if (argc > 2 && ft_strequ(argv[1], "-c"))
	{
		return (EXIT_SUCCESS);
	}
	main_loop(env); */
	return (g_status);
}

