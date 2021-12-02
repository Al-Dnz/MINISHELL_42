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

void	run(char *line, char **env)
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