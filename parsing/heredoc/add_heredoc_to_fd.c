/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_heredoc_to_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:10:47 by odx               #+#    #+#             */
/*   Updated: 2024/07/06 22:12:46 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_heredoc(t_cmd *cmd, int *i)
{
	*i = 0;
	cmd->fd_heredoc[0] = -1;
	cmd->fd_heredoc[1] = -1;
}

bool	add_heredoc_to_fd(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;

	current = cmd;
	while (current != NULL)
	{
		if (current->redir)
		{
			init_heredoc(current, &i);
			while (current->redir[i])
			{
				if (current->redir[i][0] == '-')
				{
					if ((pipe(current->fd_heredoc)) == -1)
						return (perror("pipe"), false);
					ft_putstr_fd(current->redir[i] + 1, current->fd_heredoc[1]);
					close(current->fd_heredoc[1]);
				}
				i++;
			}
		}
		current = current->next;
	}
	return (true);
}
