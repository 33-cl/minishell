/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:56:10 by odx               #+#    #+#             */
/*   Updated: 2024/07/05 13:56:31 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	redir_error_after(t_args	*current)
{
	if (ft_strcmp(current->value, ">") == 0 && current->quotes == 0)
	{
		if (current->prev && ft_strcmp(current->prev->value, "<") == 0 \
		&& current->prev->type != T_HEREDOC)
			return (printf("Error: %s\n", ERROR_NEWLINE), false);
	}
	if ((ft_strcmp(current->value, "<") == 0 || ft_strcmp \
		(current->value, ">") == 0 || ft_strcmp(current->value, \
		"<<") == 0 || ft_strcmp(current->value, ">>") == 0 || \
		ft_strcmp(current->value, "<<<") == 0) && current->quotes == 0)
	{
		if (current->prev && current->prev->type != T_HEREDOC && \
		(ft_strcmp(current->prev->value, "<") == 0 || ft_strcmp \
		(current->prev->value, ">") == 0 || ft_strcmp(current->prev->value, \
		"<<") == 0 || ft_strcmp(current->prev->value, ">>") == 0 || \
		ft_strcmp(current->prev->value, "<<<") == 0))
			return (printf("Error: syntax error near unexpected token %s\n", \
			current->value), false);
		else if (current->next == NULL && current->prev->type != T_HEREDOC)
			return (printf("Error: %s\n", ERROR_NEWLINE), false);
	}
	return (true);
}

bool	redir_error(t_args	*current)
{
	if (ft_strcmp(current->value, ">") == 0 && current->quotes == 0)
	{
		if (current->prev && ft_strcmp(current->prev->value, "<") == 0)
			return (printf("Error: %s\n", ERROR_NEWLINE), false);
	}
	if ((ft_strcmp(current->value, "<") == 0 || ft_strcmp \
		(current->value, ">") == 0 || ft_strcmp(current->value, \
		"<<") == 0 || ft_strcmp(current->value, ">>") == 0 || \
		ft_strcmp(current->value, "<<<") == 0) && current->quotes == 0)
	{
		if (current->prev && (ft_strcmp(current->prev->value, "<") == 0 || \
		ft_strcmp(current->prev->value, ">") == 0 || ft_strcmp(current->prev->\
		value, "<<") == 0 || ft_strcmp(current->prev->value, ">>") == 0 || \
		ft_strcmp(current->prev->value, "<<<") == 0))
			return (printf("Error: syntax error near unexpected token %s\n", \
			current->value), false);
		else if (current->next == NULL)
			return (printf("Error: %s\n", ERROR_NEWLINE), false);
	}
	return (true);
}
