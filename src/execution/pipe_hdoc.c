#include "minishell.h"

char	*free_rdl_str(void)
{
	free(g_data.str);
	g_data.str = NULL;
	return (NULL);
}

char	*str_error2(char *s, char *ret, int status)
{
	ft_putendl_fd(s, 2);
	g_data.status = status;
	return (ret);
}

int	read_hdoc(char *str)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
		clean_exit(0, 3);
	write(pfd[1], str, ft_strlen(str));
	close(pfd[1]);
	return (pfd[0]);
}

char	*rdl_hdoc(t_hdoc *hdoc)
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
			(g_data.str) = ft_strjoin_special(g_data.str, line, 0);
		(g_data.str) = ft_strjoin_special(g_data.str, "\n", 0);
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

void	fork_chd_rdl_hdoc(int *pfd, t_hdoc *hdoc)
{
	int		hdoc_fd;
	char	*buf;
	char	*hdoc_inp;
	t_hdoc	*tmp;

	tmp = hdoc;
	while (tmp != NULL)
	{
		hdoc_inp = rdl_hdoc(tmp);
		if (hdoc_inp != NULL)
		{
			close(pfd[0]);
			hdoc_fd = read_hdoc(hdoc_inp);
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

int	add_fd_redir(t_btree *node, int fd)
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

int	fork_par_rdl_hdoc(int *pfd, pid_t pid, t_btree *node)
{
	int		status;

	status = 0;
	pid = wait(&status);
	close(pfd[1]);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) == 130)
			return (1);
	add_fd_redir(node, pfd[0]);
	return (0);
}

int	fork_rdl_hdoc(t_btree *node)
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
	if (pid > 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		if (fork_par_rdl_hdoc(pfd, pid, node) == 1)
			return (1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, &handler_sigint);
		fork_chd_rdl_hdoc(pfd, node->hdoc);
	}
	return (0);
}