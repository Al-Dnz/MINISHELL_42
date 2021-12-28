/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:07:49 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:10:54 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(char **arr, char **envp)
{
	char	*cmd_path;

	if (is_env_unset("PATH"))
		cmd_path = ft_strdup(arr[0]);
	else
		cmd_path = find_path(arr[0]);
	if (ft_strequ(arr[0], "minishell")
		|| cmd_path == NULL || execve(cmd_path, arr, envp) == -1)
	{
		ft_strclr(&cmd_path);
		error_cmd(arr[0], 2, 127);
		clean_program();
		exit(127);
		return ;
	}
	ft_strclr(&cmd_path);
}

/*
**	Return value of the signal in child process
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

void	child_status(int status)
{
	if (WIFSIGNALED(status))
		g_data.status = WTERMSIG(status);
	else if (WIFEXITED(status))
		g_data.status = WEXITSTATUS(status);
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

void	fork_execve(t_btree *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	g_data.child_pid = pid;
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		signal(SIGCHLD, NULL);
		signal(SIGINT, SIG_IGN);
		pid = waitpid(pid, &status, WUNTRACED);
		if (pid == -1)
			return ;
		child_status(status);
		clean_process();
	}
	else if (pid == 0)
		ft_execve(node->arr, g_data.env);
}
