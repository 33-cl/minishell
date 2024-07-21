/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:42:32 by odx               #+#    #+#             */
/*   Updated: 2024/07/21 17:50:40 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_redirections(char **redir)
{
	int	i;

	i = 0;
	while (redir[i] != NULL)
	{
		free(redir[i]);
		i++;
	}
	free(redir);
}

void	free_command(t_command **command)
{
	t_command	*current;
	t_command	*next;

	current = *command;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->args)
			free_args(&current->args);
		if (current->heredoc_delimiters)
			free_heredoc_delimiters(current->heredoc_delimiters);
		if (current->redir)
			free_redirections(current->redir);
		free(current);
		current = next;
	}
	*command = NULL;
}

void	free_command_before(t_command **command)
{
	t_command	*current;
	t_command	*next;

	current = *command;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->args)
			free_args(&current->args);
		if (current->heredoc_delimiters)
			free(current->heredoc_delimiters);
		if (current->redir)
			free_redirections(current->redir);
		free(current);
		current = next;
	}
	*command = NULL;
}

void	free_resources(char *name, char *value, t_env **current)
{
	free(name);
	free(value);
	free_env(current);
}

void	free_everything(t_command *command, char *input, t_env *env)
{
	free_final_list(&command->final_cmd);
	free_command_before(&command);
	free_env(&env);
	if (input)
		free(input);
	input = NULL;
}
