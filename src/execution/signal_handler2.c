#include "minishell.h"

void	exit_by_signal(void)
{
	int	status;

	write(1, "\nexit\n", 6);
	status = g_status;
	clean_program();
	exit(status);
}
