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

void		formalize_env_path(char **env_tab);
char		*find_path(char *cmd);

void		multi_pipeline(char ***matrix, char **env);
void		run(char *line, char **env);

#endif