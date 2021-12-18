#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
 #include <fcntl.h>

# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
//# include <curses.h>
//# include <term.h>

# include "../libft/libft.h"

# define REDIR_OP 1
# define FILE 2
# define CMD 3

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

/*
** 	REDIR KIND
**	
**	<	1
**	>	2
**	<<	3
**	>>	4
*/


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
	char			*end_word;
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
	char			**arr;
	struct s_btree	*left;
	struct s_btree	*right;
}				t_btree;

typedef struct s_data
{
	int		chd_status;
	int		exit_status;
	int		displayer;
	int		err;
	char	*token_err;
	char	**token_tab;
	int		index;
	char 	**env;

	t_btree	*tree;
	pid_t	child_pid;
	int		status;
	int		quit;

	char	*str;
	int 	in_hdoc;
	int		stop;
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
int	is_word(char *str);


t_btree	*create_node(t_btree *left, t_btree *right);
int		free_btree(t_btree *node);

t_redir	*new_redir(char *str);
void	del_redir(t_redir *redir);
void	redir_clr(t_redir **redir);
int 	redir_add_back(t_redir **redir, char *str);
t_redir	*ft_redirlast(t_redir *redir);

t_arg	*new_arg(char *str);
void	del_arg(t_arg *arg);
void	arg_clr(t_arg **arg);
int 	arg_add_back(t_arg **arg, char *str);
t_arg	*ft_arglast(t_arg *arg);


int	unquoted_string_size(char *str);
int	quoted_string_size(char *str, char quote);
int	operator_size(char *line);
int	token_size(char *line);

int	count_token(char *line);
char	**create_token_tab(int size);
int	get_all_token(char *line);

int	save_node_cmd(t_btree **node, char *str);
int	save_node_redir(t_btree **node, char *str);
int save_node_redir_file(t_btree **node, char *str);
int	set_node(t_btree **node);
int	tree_constructor(void);

void	display_arg(t_arg *arg);
void	display_redir(t_redir *redir);
void	display_hdoc(t_hdoc *hdoc);
void 	display_tree(t_btree *node);

//----------------------------------------------------------------
char	*ft_strjoin_special(char *s1, char *s2, int nb);
char	*ft_strjoin_special_2(char **s1, char **s2, int nb);
char	*revert_null_str(char *dest, char *src);
void	free_mode(char **str1, char **str2, int mode);

char	*get_exp(char **str);
char	*ft_replace_str(char *str);
char	*store_exp_unq(char **str, char type);
char	*store_dollar(char **str);
char	*token_cleaner(char *str);
//----------------------------------------------------------------

void	set_arg_tab(t_btree **tree);
char	**arglist_to_tab(t_arg *arg);

//--------------------------EXECUTION-------------------------------------
void	ft_execve(char **arg, char **envp);
void	child_status(int status);
void	fork_execve(t_btree *node);

int		launch_command(t_btree *node, char *cmd);
void	launch_pipe(t_btree *node);
int		launch_tree(t_btree *tree);

void	error_message(char *str, int fd, int status);
void	clean_program(void);
void	clean_exit(int status, int error);

int	valid_redir(t_btree *node);
int	launch_redir(t_redir *redir);

//---------------SIGNAL------------------------------------------------

void	handler_sigchild(int sig);
void	handler_sigint(int sig);
void	handler_sigquit(int sig);
void	ctrl_d(void);

//-------------HEREDOC----------------------------------------

void	del_hdoc(t_hdoc *hdoc);
void	hdoc_clr(t_hdoc **hdoc);
t_hdoc	*ft_hdoclast(t_hdoc *hdoc);
int 	hdoc_add_back(t_hdoc **hdoc, char *str);


int	set_tree_hdoc(t_btree **tree);
int	set_node_hdoc(t_btree **node);


int	read_hdoc(char *str);
char	*hdoc_readline(t_hdoc *hdoc);
void	hdoc_child_process(int *pfd, t_hdoc *hdoc);
int	hdoc_parent_process(int *pfd, pid_t pid, t_btree *node);
int	hdoc_pipe(t_btree *node);

char	*free_rdl_str(void);
char	*str_error2(char *s, char *ret, int status);
int	is_last_hdoc(t_redir *redir);
int	set_fd_redir(t_btree *node, int fd);

int	launch_pipe_hdoc(t_btree *tree);



#endif