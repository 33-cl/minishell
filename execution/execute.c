/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:30:04 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/03 17:03:27 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	run_command(t_cmd *cmd, int *status, t_env *env, t_process *infos)
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
			if (!exec_execve(cmd, pipefd, env, infos))
				return (-1);
	}
	if (cmd->redir_out)
	{
		cmd->redir_out = 0;
		if (dup2(infos->stdin, STDOUT_FILENO) == -1)
			return (-1);
		close(infos->stdout);
	}
	return (0);
}

/*
	Executes the command
	Returns a status or -1 in case of error
*/

int	execute(t_cmd *command, t_env *env, int status)
{
	t_process		*infos;
	int				exec;

	infos = NULL;
	infos = init_execution(infos, command);
	if (!infos)
		return (reset_std(infos), -1);
	while (command != NULL)
	{
		if (get_in(command) == -1)
			return (reset_std(infos), free(infos->pids), 1);
		if (get_out(command) == -1)
			return (reset_std(infos), free(infos->pids), 1);
		if (run_command(command, &status, env, infos) == -1)
			return (wait_pids(infos, &status, exec), reset_std(infos),
				free(infos->pids), -1);
		if (command->exec == EXECVE)
			infos->nb_pids++;
		exec = command->exec;
		command = command->next;
	}
	wait_pids(infos, &status, exec);
	free(infos->pids);
	reset_std(infos);
	return (free(infos), status);
}
