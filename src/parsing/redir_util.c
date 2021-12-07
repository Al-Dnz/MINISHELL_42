#include "minishell.h"

t_redir	*new_redir(char *str)
{
	t_redir	*element;
	static char *sym_arr[4] = {"<", ">", "<<", ">>"};

	element = malloc(sizeof(t_redir));
	if (element == NULL)
		return (NULL);
	if (ft_str_index(str, sym_arr) != -1)
		element->kind = ft_str_index(str, sym_arr) + 1;
	else
		element->kind = 0;
	element->file = NULL;
	element->hdoc_fd = -1;
	element->next = NULL;
	return (element);
}

void	del_redir(t_redir *redir)
{
	if (redir == NULL)
		return ;
	ft_strclr(&redir->file);
	redir->hdoc_fd = 0;
}

void	redir_clr(t_redir **redir)
{
	t_redir	*tmp;

	if (*redir == NULL)
		return ;
	if ((*redir)->next != NULL)
		tmp = (*redir)->next;
	else
		tmp = NULL;
	del_redir(*redir);
	free(*redir);
	*redir = tmp;
	redir_clr(&(*redir));
}
