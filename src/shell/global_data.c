#include "minishell.h"

t_data	*data(void)
{
	static t_data	*global_data = NULL;

	if (global_data)
		return (global_data);
	global_data = ft_calloc(sizeof(t_data), 1);
	return (global_data);
}