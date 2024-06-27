/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:36:57 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/19 20:31:54 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	t_args	*current;

	current = command->args;
	// while (current != NULL)
	// {
	// 	if (!double_quote_ok(current->value))
	// 		return (false);
	// 	if (!single_quote_ok(current->value))
	// 		return (false);
	// 	current = current->next;
	// }
	if (!syntax_operator_after(command))
		return (false);
	return (true);
}

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
		else if (current->prev == NULL && current->next->type == T_PIPE && current->prev->type != T_HEREDOC)
			return (printf("Error: %s\n", ERROR_PIPE_PIPE), false);
		else if (current->prev == NULL)
			return (printf("Error: %s\n", ERROR_PIPE), false);
		else if (current->prev && current->prev->type == T_PIPE && current->prev->type != T_HEREDOC)
			return (printf("Error: %s\n", ERROR_PIPE_PIPE), false);
		else if (current->next && current->next->type == T_PIPE && current->prev->type != T_HEREDOC)
			return (printf("Error: %s\n", ERROR_PIPE_PIPE), false);
		else if (current->prev && current->prev->type != T_HEREDOC && (ft_strcmp(current->prev->value, "<") == 0 || ft_strcmp \
		(current->prev->value, ">") == 0 || ft_strcmp(current->prev->value, \
		"<<") == 0 || ft_strcmp(current->prev->value, ">>") == 0) && \
		current->prev->quotes == 0)
			return (printf("Error: %s\n", ERROR_PIPE), false);	
	}
	return (true);
}
// gerer les chaines vides remplies de white space
// checker direc quand il ya beaucoup de redirections
// minishell> echo hi | |
// Error: syntax error near unexpected token `||'

bool	redir_error_after(t_args	*current)
{

	if (ft_strcmp(current->value, ">") == 0 && current->quotes == 0)
	{
		if (current->prev && ft_strcmp(current->prev->value, "<") == 0 && current->prev->type != T_HEREDOC)
			return (printf("Error: %s\n", ERROR_NEWLINE), false);
	}
	if ((ft_strcmp(current->value, "<") == 0 || ft_strcmp \
		(current->value, ">") == 0 || ft_strcmp(current->value, \
		"<<") == 0 || ft_strcmp(current->value, ">>") == 0 || ft_strcmp(current->value, "<<<") == 0) && current->quotes == 0)
	{
		if (current->prev && current->prev->type != T_HEREDOC && (ft_strcmp(current->prev->value, "<") == 0 || ft_strcmp \
		(current->prev->value, ">") == 0 || ft_strcmp(current->prev->value, \
		"<<") == 0 || ft_strcmp(current->prev->value, ">>") == 0 || ft_strcmp(current->prev->value, "<<<") == 0))
			return (printf("Error: syntax error near unexpected token %s\n", current->value), false);
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
		"<<") == 0 || ft_strcmp(current->value, ">>") == 0 || ft_strcmp(current->value, "<<<") == 0) && current->quotes == 0)
	{
		if (current->prev && (ft_strcmp(current->prev->value, "<") == 0 || ft_strcmp \
		(current->prev->value, ">") == 0 || ft_strcmp(current->prev->value, \
		"<<") == 0 || ft_strcmp(current->prev->value, ">>") == 0 || ft_strcmp(current->prev->value, "<<<") == 0))
			return (printf("Error: syntax error near unexpected token %s\n", current->value), false);
		else if (current->next == NULL)
			return (printf("Error: %s\n", ERROR_NEWLINE), false);	
	}
	return (true);
}

bool	syntax_operator_ok(t_command *command)
{
	t_args *current;

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
	t_args *current;

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

bool	double_quote_ok(char *input)
{
	bool	inside_double_quote;
	bool	inside_single_quote;
	int		i;

	inside_double_quote = false;
	inside_single_quote = false;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' && !inside_double_quote)
			inside_single_quote = !inside_single_quote;
		else if (input[i] == '"' && !inside_single_quote)
			inside_double_quote = !inside_double_quote;
		i++;
	}
	if (inside_double_quote)
	{
		printf("Error: Unclosed double quote.\n");
		return (false);
	}
	return (true);
}
bool	single_quote_ok(char *input)
{
	bool	inside_double_quote;
	bool	inside_single_quote;
	int		i;

	inside_double_quote = false;
	inside_single_quote = false;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '"' && !inside_single_quote)
			inside_double_quote = !inside_double_quote;
		else if (input[i] == '\'' && !inside_double_quote)
			inside_single_quote = !inside_single_quote;
		i++;
	}
	if (inside_single_quote)
	{
		printf("Error: Unclosed single quote.\n");
		return (false);
	}
	return (true);
}