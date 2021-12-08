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

typedef struct	s_split
{
	int		k;
	int		i;
	int		j;
	int		len;
	int		count_words;
	char	c;
	char	**str;
}				t_split;

/////////////////////////////////////////////

typedef struct s_redir
{
	int				kind;
	char			*file;
	int				hdoc_fd;
	struct s_redir	*next;
}				t_redir;

typedef struct s_hdoc
{
	int				fd;
	char			*end;
	struct s_hdoc	*next;
}		t_hdoc;

typedef	struct s_arg
{	
	char *word;
	struct s_arg *next;
}		t_arg;

typedef struct s_btree
{
	t_arg			*arg;
	t_redir			*redir;
	t_hdoc			*hdoc;
	struct s_btree	*left;
	struct s_btree	*right;
}				t_btree;

typedef struct s_data
{
	int		err;
	char	*token_err;
	char	**token_tab;
} t_data;

t_data	g_data;

void		formalize_env_path(char **env_tab);
char		*find_path(char *cmd);

static inline void		multi_pipeline(char ***matrix, char **env);
void		run(char *line, char **env);

void		print_error(void);

int			check_syntax_redir(char *line, int i);
int 		check_syntax(char *line);

void			ft_free_begin_tab(char **str, int index);
int				protection(char const *s, int i, char c, t_split *split);
void			ft_write_words_util(char const *s, t_split *sp);
void			ft_write_words_minishell(char const *s, int words, t_split *sp);

char		**ft_special_split(char const *s, char c);


int	is_quote(char c);
int	is_operator(char c);
int	is_pipe_op(char c);
int	is_redir_op(char *str);


t_redir	*new_redir(char *str);
void	del_redir(t_redir *redir);
void	redir_clr(t_redir **redir);

t_arg	*new_arg(char *str);
void	del_arg(t_arg *arg);
void	arg_clr(t_arg **arg);

int	unquoted_string_size(char *str);
int	quoted_string_size(char *str, char quote);
int	operator_size(char *line);
int	token_size(char *line);

int	count_token(char *line);
char	**create_token_tab(int size);
int	get_all_token(char *line);



#endif