/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:36:57 by qordoux           #+#    #+#             */
/*   Updated: 2024/07/07 16:22:52 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	syntax_error(t_command	*command)
{
	t_args	*current;

	current = command->args;
	while (current != NULL)
	{
		if (!double_quote_ok(current->value))
			return (false);
		if (!single_quote_ok(current->value))
			return (false);
		current = current->next;
	}
	if (!syntax_operator_ok(command))
		return (false);
	return (true);
}

bool	syntax_error_after(t_command	*command)
{
	if (!syntax_operator_after(command))
		return (false);
	return (true);
}

bool	syntax_operator_ok(t_command *command)
{
	t_args	*current;

	current = command->args;
	while (current != NULL)
	{
		if (!pipe_error(current))
			return (false);
		if (!redir_error(current))
			return (false);
		current = current->next;
	}
	return (true);
}

bool	syntax_operator_after(t_command *command)
{
	t_args	*current;

	current = command->args;
	while (current != NULL)
	{
		if (current->type == T_HEREDOC)
		{
			current = current->next;
		}
		if (current != NULL)
		{
			if (!pipe_error_after(current))
				return (false);
			if (!redir_error_after(current))
				return (false);
			current = current->next;
		}
	}
	return (true);
}
