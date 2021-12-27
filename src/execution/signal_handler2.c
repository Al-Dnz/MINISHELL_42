#include "minishell.h"

void	exit_by_signal(void)
{
	write(1, "\nexit\n", 6);
	clean_program();
	exit(g_data.status);
}
