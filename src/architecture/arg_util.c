#include "minishell.h"

t_arg	*new_arg(char *str)
{
	t_arg	*element;

	element = malloc(sizeof(t_arg));
	if (element == NULL)
		return (NULL);
	element->word = ft_strdup(str);
	if (element->word == NULL)
		return (NULL);
	element->next = NULL;
	return (element);
}

void	del_arg(t_arg *arg)
{
	if (arg == NULL)
		return ;
	ft_strclr(&arg->word);
}

void	arg_clr(t_arg **arg)
{
	t_arg	*tmp;

	if (*arg == NULL)
		return ;
	if ((*arg)->next != NULL)
		tmp = (*arg)->next;
	else
		tmp = NULL;
	del_arg(*arg);
	free(*arg);
	*arg = tmp;
	arg_clr(&(*arg));
}

int arg_add_back(t_arg **arg, char *str)
{
	t_arg *element;

	element = new_arg(str);
	if (element == NULL)
		return (0);
	if ((*arg) == NULL)
	{
		(*arg) = element;
		return (0);
	}
	while ((*arg)->next != NULL)
		(*arg) = (*arg)->next;
	(*arg)->next = element;
	return (1);
}