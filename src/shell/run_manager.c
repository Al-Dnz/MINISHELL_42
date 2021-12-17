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
/* 	ft_print_tab(g_data.token_tab);
	ft_putstr_fd("\n", 1); */

	int i = 0;
	while (g_data.token_tab[i])
	{
		g_data.token_tab[i] = ft_replace_token(g_data.token_tab[i]);
		i++;
	}

	//AST
	tree_constructor();

	//builtins
	if (g_data.tree && g_data.tree->arg[0].word)
	{
		if (!ft_strcmp(g_data.tree->arg[0].word, "echo"))
			echo(g_data.tree->arg);
		if (!ft_strcmp(g_data.tree->arg[0].word, "pwd"))
			pwd(1);
		if (!ft_strcmp(g_data.tree->arg[0].word, "cd"))
			cd(g_data.tree->arg);
/* 		if (!ft_strcmp(g_data.tree->arg[0].word, "env"))
			cmd_env(g_data.tree->arg); */
		if (!ft_strcmp(g_data.tree->arg[0].word, "env"))
			cmd_env(g_data.tree->arg);
		if (!ft_strcmp(g_data.tree->arg[0].word, "export"))
			export(g_data.tree->arg);
		if (!ft_strcmp(g_data.tree->arg[0].word, "unset"))
			unset(g_data.tree->arg);
	}

//	display_tree(g_data.tree);
	ft_free_tab(g_data.token_tab);
	free_btree(g_data.tree, 0);

	//token cleaner
/* 	char *str;
	str = ft_replace_token(g_data.token_tab[0]);
	printf("[%s]=>[%s]\n",g_data.token_tab[0], str); */
}