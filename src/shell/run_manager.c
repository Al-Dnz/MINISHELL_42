#include "minishell.h"

static inline void multi_pipeline(char ***matrix, char **env)
{
	int fd[2];
	pid_t pid;
	int fdd = 0; //backup
	int i = 0;
	char *cmd_path = NULL;

	while (matrix[i] != NULL)
	{
		pipe(fd);
		pid = fork();
		ft_strclr(&cmd_path);
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			dup2(fdd, 0);
			if (matrix[i + 1] != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			cmd_path = find_path(matrix[i][0]);
			execve(cmd_path, matrix[i], env);
			exit(1);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fdd = fd[0];
			i++;
		}
	}
}

void	run_multipipe(char *line, char **env)
{
	char ***matrix;
	char **table;
	int index;

	table = ft_split(line, "|");
	matrix = matrix_gen(ft_tabsize(table));
	index = 0;
	while (index < ft_tabsize(table))
	{
		matrix[index] = ft_split(table[index], "	 ");
		index++;
	}
	multi_pipeline(matrix, env);
	ft_free_tab(table);
	free_matrix(matrix);
}

void	run(char *line, char **env)
{
	(void)env;
	g_data.displayer = 0;

	if (get_all_token(line) == 0)
		return ;
	//affichage tableau
	// ft_print_tab(g_data.token_tab);
	// ft_putstr_fd("\n", 1);

	/*
	** on duplique les stdin et stdout pour eviter de quiter la boucle
	*/

	int	std_out;
	int	std_in;
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);

	//AST test
	tree_constructor();
	set_arg_tab(&g_data.tree);
	set_tree_hdoc(&g_data.tree);
	g_data.displayer = 0;
	// display_tree(g_data.tree);

	g_data.env = env;

	if (valid_redir(g_data.tree) == 0)
		return ;
	//SECURE CODE
	launch_tree(g_data.tree);
	free_btree(g_data.tree);
	ft_free_tab(g_data.token_tab);
	dup2(std_out, STDOUT_FILENO);
	dup2(std_in, STDIN_FILENO);

	

	

	// char *s1 = find_path("ls");
	// printf("{%s}\n", s1);

	//ft_print_tab(g_data.env);
	// char *envp;
	// char **env_tab;
	// envp = getenv("PATH");
	// env_tab = ft_split(envp, ":");
	//formalize_env_path(env_tab);
	// write(1, "\n---\n", 5);
	// ft_print_tab2(env_tab);

	//printf("{%s}\n", find_path(line));



	
	

	



	//ft_print_tab(g_data.env);
	// rl_on_new_line();
	// rl_replace_line("", 0);

	//token cleaner test
	// char *str;
	// str = token_cleaner(g_data.token_tab[0]);
	// printf("[%s]=>[%s]\n",g_data.token_tab[0], str);
}