/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:30:04 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/26 19:13:09 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	run_command(t_cmd *cmd, int *status, t_env *env, pid_t *pid, t_streams *std, int i)
{
	int	pipefd[2];

	if (cmd->args[0] != NULL)
	{
		if (cmd->next != NULL)
			if (pipe(pipefd) == -1)
				return (-1);
		if (is_a_builtin(cmd->args[0]))
		{
			if (!exec_builtin(cmd, status, pipefd, env))
				return (-1);
		}
		else
			if (!exec_execve(pid, cmd, pipefd, env, std, i))
				return (-1);
	}
	if (cmd->redir_out)
	{
		cmd->redir_out = 0;
		if (dup2(std->in, STDOUT_FILENO) == -1)
			return (-1);
		close(std->out);
	}
	return (0);
}

/*
	Executes the command
	Returns a status or -1 in case of error
*/

int	execute(t_cmd *command, t_env *env, int status)
{
	t_streams	std;
	pid_t		*pids;
	int			i;
	int			exec;

	if (!init_execution(&pids, &std, command, &i))
		return (reset_std(&std), -1);
	i = 0;
	while (command != NULL)
	{
		if (get_in(command) == -1)
			return (reset_std(&std), free(pids), 1);
		if (get_out(command) == -1)
			return (reset_std(&std), free(pids), 1);
		if (run_command(command, &status, env, &pids[i], &std, i) == -1)
			return (wait_pids(i, pids, &status, exec), reset_std(&std), free(pids), -1);
		if (command->exec == EXECVE)
			i++;
		exec = command->exec;
		command = command->next;
	}
	wait_pids(i, pids, &status, exec);
	free(pids);
	reset_std(&std);
	return (status);
}
