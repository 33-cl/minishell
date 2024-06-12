/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:30:04 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/08 22:28:22 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int	run_command(t_cmd *command, int *status, t_env *env, pid_t pid, t_streams *std)
{
	int	pipefd[2];

	if (command->args[0] != NULL)
	{
		if (command->next != NULL)
			if (pipe(pipefd) == -1)
				return (-1);
		if (is_a_builtin(command->args[0]))
		{
			if (!exec_builtin(command, status, pipefd, env))
				return (-1);
		}
		else
			if (!exec_execve(pid, command, pipefd, env))
				return (-1);
	}
	if (command->redir_out)
	{
		command->redir_out = 0;
		if (dup2(std->in, STDOUT_FILENO) == -1)
			return (-1);
		close(std->out);
	}
	return (0);
}

/*
	Execute la commande prise en entree
	Renvoie un status ou -1 en cas d'erreur dans une fonction du code
*/

int execute(t_cmd *command, t_env *env, int status)
{
	t_streams	std;
	pid_t		*pids;
	int			i;
	int			exec;

	if (!init_execution(&pids, &std, command, &i))
		return (-1);
	i = 0;
	while (command != NULL)
	{
		if (get_out(command) == -1)
			return (reset_std(std.in, std.out), 1);
		if (get_in(command) == -1)
			return (reset_std(std.in, std.out), 1);
		if (i++, run_command(command, &status, env, pids[i], &std) == -1)
			return (wait_pids(i, pids, &status, exec), free(pids), -1);
		exec = command->exec;
		command = command->next;
	}
	wait_pids(i, pids, &status, exec);
	free(pids);
	reset_std(std.in, std.out);
	return (status);
}
