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
	data()->exit_status = status;
}

#ifdef __linux__

void	clean_program(void)
{
	rl_clear_history();
	ft_free_tab(data()->token_tab);
	data()->token_tab = NULL;
	ft_free_tab(data()->env);
	data()->env = NULL;
	free_btree(data()->tree);
	data()->tree = NULL;
	ft_strclr(&data()->str);
	if (data()->token_err)
		ft_strclr(&data()->token_err);
	data()->str = NULL;
}

#else

void	clean_program(void)
{
	ft_free_tab(data()->token_tab);
	data()->token_tab = NULL;
	ft_free_tab(data()->env);
	data()->env = NULL;
	free_btree(data()->tree);
	free(data()->tree)
	data()->tree = NULL;
	ft_strclr(&data()->str);
	if (data()->token_err)
		ft_strclr(&data()->token_err);
	data()->str = NULL;
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
	// if (isatty(0))
	// {
	clean_program();
	free(data());
	exit(status);
	// }
}
