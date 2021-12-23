#include "minishell.h"

char	*free_rdl_str(void)
{
	free(data()->str);
	data()->str = NULL;
	return (NULL);
}

char	*str_error2(char *s, char *ret, int status)
{
	ft_putendl_fd(s, 2);
	g_status = status;
	return (ret);
}

int	is_last_hdoc(t_redir *redir)
{
	if (redir == NULL)
		return (1);
	redir = redir->next;
	while (redir != NULL)
	{
		if (redir->kind == 3)
			return (0);
		redir = redir->next;
	}
	return (1);
}

int	set_fd_redir(t_btree *node, int fd)
{
	t_redir	*redir;

	redir = node->redir;
	while (redir != NULL)
	{
		if (redir->kind == 3 && is_last_hdoc(redir) == 1)
		{
			redir->hdoc_fd = fd;
			return (0);
		}
		redir = redir->next;
	}
	return (1);
}
