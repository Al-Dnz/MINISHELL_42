#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
//# include <curses.h>
//# include <term.h>

# include "../libft/libft.h"

typedef struct s_ms
{
	int		err;
	char	*token_err;
} t_ms;

t_ms	g_ms;

void		formalize_env_path(char **env_tab);
char		*find_path(char *cmd);

static inline void		multi_pipeline(char ***matrix, char **env);
void		run(char *line, char **env);

void		print_error(void);

int 		check_syntax(char *line);

#endif