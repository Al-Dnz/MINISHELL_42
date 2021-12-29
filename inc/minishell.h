/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivloisy <ivloisy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:53:26 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/29 15:49:51 by ivloisy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
**# include <curses.h>
**# include <term.h>
*/

# include "../libft/libft.h"

/*
** 	REDIR KIND
**	
**	<	1
**	>	2
**	<<	3
**	>>	4
*/

typedef struct s_fd_list
{
	int					fd;
	struct s_fd_list	*next;
}				t_fd_list;

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

typedef struct s_arg
{	
	char			*word;
	struct s_arg	*next;
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
	int			chd_status;
	int			exit_status;
	int			displayer;
	int			err;
	char		*token_err;
	char		**token_tab;
	int			index;
	char		**env;
	t_btree		*tree;
	pid_t		child_pid;
	int			status;
	int			quit;
	char		*str;
	int			in_hdoc;
	int			stop;
	int			dd;
	int			dash;
	int			std_in;
	int			std_out;
	t_fd_list	*fd_list;
}	t_data;

void		main_loop(char **env);

int			is_env_unset(char *str);
void		formalize_env_path(char **env_tab);
char		*find_path(char *cmd);

void		run(char *line, char **env);

void		print_error(void);
void		print_err_env(char *s);
void		print_basic_error(void);
void		print_opt_error(char *opt);

int			check_syntax_redir(char *line, int i);
int			check_syntax(char *line);
int			check_suit(char *line, int i);

int			is_quote(char c);
int			is_operator(char c);
int			is_pipe_op(char c);
int			is_redir_op(char *str);
int			is_word(char *str);

t_btree		*create_node(t_btree *left, t_btree *right);
int			free_btree(t_btree *node);

t_fd_list	*new_fd_list(int fd);
void		del_fd_list(t_fd_list *lst);
void		fd_list_clr(t_fd_list **lst);
t_fd_list	*ft_fd_listlast(t_fd_list *lst);
int			fd_lst_add_back(t_fd_list **lst, int fd);

t_redir		*new_redir(char *str);
void		del_redir(t_redir *redir);
void		redir_clr(t_redir **redir);
int			redir_add_back(t_redir **redir, char *str);
t_redir		*ft_redirlast(t_redir *redir);

t_arg		*new_arg(char *str);
void		del_arg(t_arg *arg);
void		arg_clr(t_arg **arg);
int			arg_add_back(t_arg **arg, char *str);
t_arg		*ft_arglast(t_arg *arg);

int			unquoted_string_size(char *str);
int			quoted_string_size(char *str, char quote);
int			operator_size(char *line);
int			token_size(char *line);

int			count_token(char *line);
char		**create_token_tab(int size);
int			get_all_token(char *line, int i, int j);

int			save_node_cmd(t_btree **node, char *str);
int			save_node_redir(t_btree **node, char *str);
int			save_node_redir_file(t_btree **node, char *str);

int			set_node(t_btree **node, int i);
int			tree_constructor(void);

void		display_fd_list(t_fd_list *list);
void		display_arg(t_arg *arg);
void		display_redir(t_redir *redir);
void		display_hdoc(t_hdoc *hdoc);
void		display_tree(t_btree *node);

char		*ft_strextend(char *s1, char *s2, int nb);
char		*ft_strextend_2(char **s1, char **s2, int nb);
char		*revert_null_str(char *dest, char *src);
void		free_mode(char **str1, char **str2, int mode);

char		*get_exp(char **str, int len);
char		*ft_replace_str(char *str);
char		*store_exp_unq(char **str, char type);
char		*store_dollar(char **str);
char		*token_cleaner(char *str);

void		set_arg_tab(t_btree **tree);
char		**arglist_to_tab(t_arg *arg);

void		ft_execve(char **arr, char **envp);
void		child_status(int status);
void		fork_execve(t_btree *node);

int			launch_command(t_btree *node, char *cmd);
void		launch_pipe(t_btree *node, pid_t pid);
int			launch_tree(t_btree *tree);

void		close_all(void);
void		error_cmd(char *cmd, int fd, int status);
void		error_message(char *str, int fd, int status);
void		clean_program(void);
void		clean_process(void);
void		clean_exit(int status, int error);

int			valid_redir(t_btree *node);
int			launch_redir(t_redir *redir);

void		signal_handler(void);
void		sigchild_handler(int sig);
void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		exit_by_signal(void);

void		del_hdoc(t_hdoc *hdoc);
void		hdoc_clr(t_hdoc **hdoc);
t_hdoc		*ft_hdoclast(t_hdoc *hdoc);
int			hdoc_add_back(t_hdoc **hdoc, char *str);

int			set_tree_hdoc(t_btree **tree);
int			set_node_hdoc(t_btree **node);

int			read_hdoc(char *str);
char		*hdoc_readline(t_hdoc *hdoc);
void		hdoc_child_process(int *pfd, t_hdoc *hdoc);
int			hdoc_parent_process(int *pfd, t_btree *node);
int			hdoc_pipe(t_btree *node);

char		*free_rdl_str(void);
char		*str_error2(char *s, char *ret, int status);
int			is_last_hdoc(t_redir *redir);
int			set_fd_redir(t_btree *node, int fd);

int			launch_pipe_hdoc(t_btree *tree);

void		echo(t_arg *arg);
void		pwd(int print);
void		cd(t_arg *arg);
void		cmd_env(t_arg *arg);
void		print_env(char **tab);
void		export(t_arg *arg);
void		unset(t_arg *arg);
void		cmd_exit(t_arg *arg);
char		*del_zero(char *s, int z);
char		*split_zero(char *s);
int			ft_str_isalnum_eq(char *s);

int			set_env(char **env);
int			change_var(char **tab, char *name, char *new, int dd);
char		*getvar_val(char *name, char **tab);
char		**dup_env(char **tab);
int			exist(char **tab, char *name);

int			ft_strcmp_special(char *s1, char *s2);

extern t_data	g_data;

#endif