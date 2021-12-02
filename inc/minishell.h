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

typedef enum e_error
{
	NO_ERROR,
	SUCCESS,
	BASIC_ERROR
}t_error;

typedef struct s_ms
{
	char	*line;
	char	*copy;
	int		error;
} t_ms;


void	error(t_ms *ms);
int		check_line(char *line);

//parsing
int		change_line(t_ms *ms);

#endif