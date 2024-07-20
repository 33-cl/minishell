/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:30:04 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/19 21:17:33 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	run_command(t_cmd *cmd, int *status, t_env *env, t_process *infos)
{
	int	pipefd[2];

	if (cmd->next != NULL)
		if (pipe(pipefd) == -1)
			return (-1);
	if (!cmd->args || !cmd->args[0] || is_a_builtin(cmd->args[0]))
	{
		if (!exec_builtin(cmd, status, pipefd, env))
			return (-1);
	}
	else
		if (cmd->args[0] != NULL && !exec_execve(cmd, pipefd, env, infos))
			return (-1);
	if (cmd->next == NULL)
		close(STDIN_FILENO);
	if (cmd->redir_out)
		if (!reset_stdin(cmd, infos))
			return (-1);
	return (0);
}

/*
	Executes the command
	Returns a status or -1 in case of error
*/

int	execute(t_cmd *command, t_env *env, int status, char **input)
{
	t_process		*infos;
	int				exec;

	infos = init_execution(NULL, command, input, env);
	if (!infos)
		return (reset_std(infos), -1);
	while (command != NULL)
	{
		command->exec = NONE;
		if (get_in(command, -1, -1) || get_out(command, -1, -1))
		{
			status = 1;
			command = command->next;
			continue ;
		}
		if (run_command(command, &status, env, infos) == -1)
			return (wait_pids(infos, &status, exec), reset_std(infos),
				free(infos->pids), free(infos), -1);
		if (command->exec == EXECVE)
			infos->nb_pids++;
		exec = command->exec;
		command = command->next;
	}
	wait_pids(infos, &status, exec);
	return (free(infos->pids), reset_std(infos), free(infos), status);
}
