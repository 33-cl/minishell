/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:54:39 by odx               #+#    #+#             */
/*   Updated: 2024/07/05 13:55:03 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	pipe_error(t_args *current)
{
	if (current->type == T_PIPE && current->quotes == 0)
	{
		if (current->next == NULL)
			return (printf("Error: %s\n", ERROR_PIPE), false);
		else if (current->prev == NULL && current->next->type == T_PIPE)
			return (printf("Error: %s\n", ERROR_PIPE_PIPE), false);
		else if (current->prev == NULL)
			return (printf("Error: %s\n", ERROR_PIPE), false);
		else if (current->prev && current->prev->type == T_PIPE)
			return (printf("Error: %s\n", ERROR_PIPE_PIPE), false);
		else if (current->next && current->next->type == T_PIPE)
			return (printf("Error: %s\n", ERROR_PIPE_PIPE), false);
		else if ((ft_strcmp(current->prev->value, "<") == 0 || ft_strcmp \
		(current->prev->value, ">") == 0 || ft_strcmp(current->prev->value, \
		"<<") == 0 || ft_strcmp(current->prev->value, ">>") == 0) && \
		current->prev->quotes == 0)
			return (printf("Error: %s\n", ERROR_PIPE), false);
	}
	return (true);
}

bool	pipe_error_after(t_args *current)
{
	if (current->type == T_PIPE && current->quotes == 0)
	{
		if (current->next == NULL && current->prev->type != T_HEREDOC)
			return (printf("Error: %s\n", ERROR_PIPE), false);
		else if (current->prev == NULL && current->next->type == T_PIPE \
		&& current->prev->type != T_HEREDOC)
			return (printf("Error: %s\n", ERROR_PIPE_PIPE), false);
		else if (current->prev == NULL)
			return (printf("Error: %s\n", ERROR_PIPE), false);
		else if (current->prev && current->prev->type == T_PIPE && \
		current->prev->type != T_HEREDOC)
			return (printf("Error: %s\n", ERROR_PIPE_PIPE), false);
		else if (current->next && current->next->type == T_PIPE && \
		current->prev->type != T_HEREDOC)
			return (printf("Error: %s\n", ERROR_PIPE_PIPE), false);
		else if (current->prev && current->prev->type != T_HEREDOC && \
		(ft_strcmp(current->prev->value, "<") == 0 || ft_strcmp \
		(current->prev->value, ">") == 0 || ft_strcmp(current->prev->value, \
		"<<") == 0 || ft_strcmp(current->prev->value, ">>") == 0) && \
		current->prev->quotes == 0)
			return (printf("Error: %s\n", ERROR_PIPE), false);
	}
	return (true);
}
