/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:38:43 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/25 15:14:42 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Allocates the (pid_t *) tab and stores the STDIN and STDOUT in a struct
	Returns a bool for malloc() error
*/

bool	init_execution(pid_t **pids, t_streams *std, t_cmd *cmd, int *i)
{
	*i = 0;
	cmd->redir_out = false;
	*pids = malloc(sizeof(int) * cmd_len(cmd));
	if (!*pids)
		return (false);
	std->in = dup(STDIN_FILENO);
	if (std->in == -1)
		return (free(pids), false);
	std->out = dup(STDOUT_FILENO);
	if (!std->out)
		return (free(pids), close(std->in), false);
	return (true);
}

/*
	wait_pid of the (pid_t *) tab
*/

void	wait_pids(int nb_commands, pid_t *pids, int *status, int exec)
{
	int	i;

	i = 0;
	while (i < nb_commands)
	{
		if (exec == EXECVE)
		{
			waitpid(pids[i], status, 0);
			if (WIFEXITED(*status))
				*status = WEXITSTATUS(*status);
		}
		else
			waitpid(pids[i], NULL, 0);
		i++;
	}
}
