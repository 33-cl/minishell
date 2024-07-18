/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:36:47 by odx               #+#    #+#             */
/*   Updated: 2024/07/17 19:57:29 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	initialize_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->heredoc_delimiters = NULL;
	cmd->nb_heredocs = 0;
	cmd->fd_heredoc[0] = 0;
	cmd->fd_heredoc[1] = 0;
	cmd->malloc_failed = false;
	cmd->redir = NULL;
	cmd->redir_out = false;
	cmd->exec = 0;
	cmd->i = 0;
	cmd->j = 0;
	cmd->next = NULL;
}

bool	init_final_list(t_cmd **list, t_command *command)
{
	int	args_size;

	(*list) = malloc(sizeof(t_cmd));
	if (!(*list))
		return (false);
	initialize_cmd(*list);
	args_size = ft_lstsize_final(command->args) + 1;
	(*list)->args = malloc((args_size + 1) * sizeof(char *));
	if (!(*list)->args)
	{
		free(*list);
		return (false);
	}
	(*list)->malloc_failed = false;
	(*list)->args[0] = NULL;
	(*list)->heredoc_delimiters = NULL;
	(*list)->nb_heredocs = 0;
	(*list)->redir = NULL;
	(*list)->next = NULL;
	return (true);
}

bool	init_new_final_list_node(t_cmd **head, \
t_cmd **current, t_command *command)
{
	t_cmd	*new_node;

	if (!init_final_list(&new_node, command))
		return (false);
	if (*head == NULL)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
	return (true);
}

void	init_command_fields(t_command *command)
{
	command->cmd = NULL;
	command->args = NULL;
	command->heredoc_delimiters = NULL;
	command->nb_heredocs = 0;
	command->fd_heredoc = -1;
	command->redir = NULL;
	command->final_cmd = NULL;
	command->next = NULL;
}

void	initialize_vars(int *i, t_env **current, char **name, char **value)
{
	*i = -1;
	*current = NULL;
	*name = NULL;
	*value = NULL;
}
