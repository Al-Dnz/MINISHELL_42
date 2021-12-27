/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:08:11 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:08:11 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_hdoc(char *str)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
		clean_exit(0, 3);
	write(pfd[1], str, ft_strlen(str));
	close(pfd[1]);
	return (pfd[0]);
}

char	*hdoc_readline(t_hdoc *hdoc)
{
	char	*line;

	g_data.in_hdoc = 1;
	line = readline("> ");
	if (line == NULL)
		return (str_error2("minishell: warning: << here-document >>", NULL, 0));
	while (ft_strcmp(line, hdoc->end_word))
	{
		if (g_data.str == NULL)
			g_data.str = ft_strdup(line);
		else
			(g_data.str) = ft_strextend(g_data.str, line, 0);
		(g_data.str) = ft_strextend(g_data.str, "\n", 0);
		free(line);
		line = readline("> ");
		if (line == NULL)
			return (str_error2("minishell: warning: << here-document >>",
					g_data.str, 0));
	}
	g_data.in_hdoc = 0;
	free(line);
	if (hdoc->next == NULL)
		return (g_data.str);
	return (free_rdl_str());
}

void	hdoc_child_process(int *pfd, t_hdoc *hdoc)
{
	int		hdoc_fd;
	char	*buf;
	char	*input;
	t_hdoc	*tmp;

	tmp = hdoc;
	while (tmp != NULL)
	{
		input = hdoc_readline(tmp);
		if (input != NULL)
		{
			close(pfd[0]);
			hdoc_fd = read_hdoc(input);
			buf = ft_calloc(2, sizeof(char *));
			if (buf == NULL)
				return ;
			while (read(hdoc_fd, buf, 1))
				write(pfd[1], buf, ft_strlen(buf));
			free(buf);
			close(hdoc_fd);
			close(pfd[1]);
		}
		tmp = tmp->next;
	}
	clean_exit(0, 0);
}

int	hdoc_parent_process(int *pfd, t_btree *node)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = wait(&status);
	close(pfd[1]);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) == 130)
			return (1);
	set_fd_redir(node, pfd[0]);
	return (0);
}

int	hdoc_pipe(t_btree *node)
{
	int		pfd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (g_data.stop == 1 || node->hdoc == NULL || pipe(pfd) == 1)
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		signal(SIGINT, &sigint_handler);
		hdoc_child_process(pfd, node->hdoc);
	}
	else if (pid > 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		if (hdoc_parent_process(pfd, node) == 1)
			return (1);
	}
	return (0);
}
