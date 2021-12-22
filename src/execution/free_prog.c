#include "minishell.h"

void	error_cmd(char *cmd, int fd, int status)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(": ", fd);
	error_message("command not found", fd, status);
}

void	error_message(char *str, int fd, int status)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	g_data.exit_status = status;
}

#ifdef __linux__

void	clean_program(void)
{
	write(1, "linux\n", 6);
	rl_clear_history();
	ft_free_tab(g_data.token_tab);
	g_data.token_tab = NULL;
/* 	ft_free_tab(g_data.env);
	g_data.env = NULL; */
	free_btree(g_data.tree);
	g_data.tree = NULL;
	ft_strclr(&g_data.str);
	g_data.str = NULL;
}

#else

void	clean_program(void)
{
	write(1, "macos\n", 6);
	ft_free_tab(g_data.token_tab);
	g_data.token_tab = NULL;
/* 	ft_free_tab(g_data.env);
	g_data.env = NULL; */
	free_btree(g_data.tree);
	g_data.tree = NULL;
	ft_strclr(&g_data.str);
	g_data.str = NULL;
}

#endif

void	clean_exit(int status, int error)
{
	if (error == 1)
		error_message("minishell: exit: too many arguments", 2, 2);
	else if (error == 2)
		error_message("minishell: exit: need numeric argument", 2, 2);
	else if (error == 3)
		error_message("minishell: function failed", 2, status);
	else if (error == 4)
		error_message("minishell: parse error", 2, status);
	if (error == 1 || error == 2)
		status = 2;
	if (isatty(0))
	{
		clean_program();
		exit(status);
	}
}
