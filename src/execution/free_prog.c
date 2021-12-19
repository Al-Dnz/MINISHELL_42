#include "minishell.h"

void	error_message(char *str, int fd, int status)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	g_data.exit_status = status;
}

void	clean_program(void)
{
	//rl_clear_history();
	ft_free_tab(g_data.token_tab);
	free_btree(g_data.tree);
	ft_strclr(&g_data.str);

	// free_envp(sg()->env);
	// free(sg());
}

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
	clean_program();
	exit(status);
}
