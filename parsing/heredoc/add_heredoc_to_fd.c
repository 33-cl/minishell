/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_heredoc_to_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:10:47 by odx               #+#    #+#             */
/*   Updated: 2024/07/15 18:53:40 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_heredoc(t_cmd *cmd, int *i)
{
	*i = 0;
	cmd->fd_heredoc[0] = -1;
	cmd->fd_heredoc[1] = -1;
}

bool	create_and_write_pipe(t_cmd *cmd, char *redir)
{
	if (pipe(cmd->fd_heredoc) == -1)
		return (perror("pipe"), false);
	ft_putstr_fd(redir + 1, cmd->fd_heredoc[1]);
	close(cmd->fd_heredoc[1]);
	return (true);
}

bool	add_heredoc_to_fd(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;

	current = cmd;
	current->prev = NULL;
	while (current != NULL)
	{
		if (current->redir)
		{
			init_heredoc(current, &i);
			while (current->redir[i])
			{
				if (current->redir[i][0] == '-')
					if (!create_and_write_pipe(current, current->redir[i]))
						return (false);
				i++;
			}
		}
		if (current->next != NULL)
			current->next->prev = current;
		current = current->next;
	}
	return (true);
}
