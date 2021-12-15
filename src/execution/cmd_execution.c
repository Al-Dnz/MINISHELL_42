#include "minishell.h"
#include <sys/stat.h>


void	ft_execve(char **arr, char **envp)
{
	char *cmd_path;

	cmd_path = find_path(arr[0]);
	if (cmd_path == NULL)
	{
		//SECURE CODE
		clean_exit(127, 1);
		return ;
	}
	execve(cmd_path, arr, envp);
	ft_strclr(&cmd_path);
	//SECURE CODE	
}

/*
	Return value of the signal in child process
*/
void	child_status(int status)
{
	if (status == 2)
	{
		write(1, "\n", 1);
		g_data.status = 130;
	}
	else if (status == 131 || g_data.quit == 1)
		g_data.status = 131;
	else if (status == 0)
		g_data.status = 0;
}

/*
**
**	WUNTRACED
**		revenir si un fils est bloqué (mais non suivi par ptrace(2)). 
**		L'état des fils suivis est fourni même sans cette option. traced 
**  WIFSIGNALED(status)
**  	renvoie vrai si le fils s'est terminé à cause d'un signal.
**  WTERMSIG(status)
**  	renvoie le numéro du signal qui a causé la fin du fils. 
**		Cette macro ne peut être évaluée que si WIFSIGNALED a renvoyé vrai.
**	WIFEXITED(status)
**		renvoie vrai si le fils s'est terminé normalement, 
**		c'est-à-dire par un appel à exit(3) ou _exit(2), 
**		ou bien par un retour de main(). 
**	WEXITSTATUS(status)
**		renvoie le code de sortie du fils. 
**		Ce code est constitué par les 8 bits de poids faibles 
**		de l'argument status que le fils a fourni à exit(3) 
**		ou à _exit(2) ou l'argument d'une commande de retour dans main(). 
**		Cette macro ne peut être évaluée que si WIFEXITED a renvoyé vrai. 
*/

void	fork_execve(t_btree *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	g_data.child_pid = pid;
	if (pid < 0)
		return ;;
	// SECURE CODE
	if (pid > 0)
	{
		signal(SIGCHLD, NULL);
		signal(SIGINT, SIG_IGN);
		pid = waitpid(pid, &status, WUNTRACED);
		if (pid == -1)
			return ;
		if (WIFSIGNALED(status))
			g_data.status = WTERMSIG(status);
		else if (WIFEXITED(status))
			g_data.status = WEXITSTATUS(status);
		child_status(status);
	}
	else if (pid == 0)
		ft_execve(node->arr, g_data.env);
}