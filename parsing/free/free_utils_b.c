/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:41:18 by odx               #+#    #+#             */
/*   Updated: 2024/07/10 17:19:03 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_args_global(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}

void	free_redir(char **redir)
{
	int	i;

	if (redir == NULL)
		return ;
	i = 0;
	while (redir[i] != NULL)
	{
		free(redir[i]);
		i++;
	}
	free(redir);
}

void	free_single_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
		free_args_global(cmd->args);
	if (cmd->redir)
		free_redir(cmd->redir);
	free(cmd);
}

void	free_single_cmd_bis(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
		free_args_global(cmd->args);
	free(cmd);
}

void	free_final_list_bis(t_cmd **final_cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (*final_cmd == NULL)
		return ;
	current = *final_cmd;
	while (current != NULL)
	{
		next = current->next;
		free_single_cmd_bis(current);
		current = next;
	}
	*final_cmd = NULL;
}
