/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:38:43 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/19 01:36:26 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Allocates the (pid_t *) tab and stores the STDIN and STDOUT in a struct
	Returns a bool for malloc() error
*/

t_process	*init_execution(t_process *infos, t_cmd *cmd
	, char **input, t_env *env)
{
	infos = malloc(sizeof(t_process) * 1);
	if (!infos)
		return (NULL);
	infos->piped = false;
	infos->input = *input;
	infos->nb_pids = 0;
	cmd->redir_out = false;
	infos->pids = malloc(sizeof(int) * cmd_len(cmd));
	if (!infos->pids)
		return (NULL);
	infos->stdin = dup(STDIN_FILENO);
	if (infos->stdin == -1)
		return (free(infos->pids), NULL);
	infos->stdout = dup(STDOUT_FILENO);
	if (!infos->stdout)
		return (free(infos->pids), close(infos->stdin), NULL);
	cmd->exec = NONE;
	infos->env = env;
	return (infos);
}

/*
	wait_pid of the (pid_t *) tab
*/

void	wait_pids(t_process *infos, int *status, int exec)
{
	int	i;

	i = 0;
	while (i < infos->nb_pids)
	{
		if (exec == EXECVE)
		{
			waitpid(infos->pids[i], status, 0);
			if (WIFEXITED(*status))
				*status = WEXITSTATUS(*status);
		}
		else
			waitpid(infos->pids[i], NULL, 0);
		i++;
	}
}
