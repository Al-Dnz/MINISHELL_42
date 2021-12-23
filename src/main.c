#include "minishell.h"

unsigned int	g_status;

static int	set_env(char **env)
{
	char	*s;
	char	**tmp;

	s = NULL;
	tmp = dup_env(env);
	if (tmp == NULL)
		return (0);
	s = ft_itoa(ft_atoi(getvar_val("SHLVL=", tmp)) + 1);
	if (s == NULL)
		return (0);
	if (data()->env)
		ft_free_tab(data()->env);
//	data()->env = change_var(tmp, "SHLVL=", s);
	data()->env = tmp;
//	tmp;
	if (!data()->env)
	{
		ft_strclr(&s);
//		ft_free_tab(tmp);
		return (0);
	}
	ft_strclr(&s);
//	ft_free_tab(tmp);
	int	i = 0;
	while (data()->env[i] != NULL)
	{
		free (data()->env[i]);
		data()->env[i] = NULL;
		i++;
	}
//	ft_free_tab(data()->env);
//	ft_print_tab2(data()->env);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	
//	ft_bzero(&g_data, sizeof(g_data));

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

