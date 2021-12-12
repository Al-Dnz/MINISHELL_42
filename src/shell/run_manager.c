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

	//ft_putnbr_fd(count_token(line), 1);
	if (get_all_token(line) == 0)
		return ;
	ft_print_tab(g_data.token_tab);
	tree_constructor();
	display_tree(g_data.tree);
	ft_free_tab(g_data.token_tab);
	free_btree(g_data.tree, 0);

	// t_btree *tree;
	// tree = NULL;
	// tree = create_node(NULL, NULL);

	// int i;
	// for (i = 0; g_data.token_tab[i]; i++)
	// {
	// 	save_node_cmd(&tree, g_data.token_tab[i]);
	// 	//display_arg(tree->arg);
	// }
		

	// set_node(&tree);
	

	//
	// ft_print_tab2(g_data.token_tab);
	//write(1, "\n", 1);
	// t_redir	*redir = NULL;
	// int i;
	// for (i = 0; g_data.token_tab[i]; i++)
	// 	redir_add_back(&redir, g_data.token_tab[i]);
	// display_redir(redir);
	//ft_free_tab(g_data.token_tab);

	//ft_retro_free_tab(g_data.token_tab);
}