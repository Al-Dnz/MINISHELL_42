#include "minishell.h"

void formalize_env_path(char **env_tab)
{
	int i;
	int j;
	char *temp;

	i = 0;
	while (env_tab[i])
	{
		temp = malloc(sizeof(char) * (ft_strlen(env_tab[i] + 2)));
		//MALLOC TO SECURE;
		j = 0;
		while (env_tab[i][j])
		{
			temp[j] = env_tab[i][j];
			j++;
		}
		temp[j++] = '/';
		temp[j] = 0;
		free(env_tab[i]);
		env_tab[i] = temp;
		i++;
	}
}

char *find_path(char *cmd)
{
	char *path;
	char *env;
	char **env_tab;
	int i;

	path = NULL;
	env = getenv("PATH");
	env_tab = ft_split(env, ":");
	formalize_env_path(env_tab);
	//ft_print_tab2(env_tab);
	path = cmd;
	i = 0;
	while (access(path, F_OK) != 0 && env_tab[i])
	{
		ft_strclr(&path);
		path = ft_strjoin(env_tab[i], cmd);
		// SECURE CODE
		// if (path == NULL)
		// 	return (NULL);
		i++;
	}
	if (access(path, F_OK) != 0)
		perror(cmd);
	ft_free_tab(env_tab);
	//printf("\n=>[%s]<=\n", path);
	return (path);
}