/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_heredoc_delimiter_and_remove_quotes.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:07:05 by odx               #+#    #+#             */
/*   Updated: 2024/07/17 20:23:46 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	add_heredoc_delimiter(t_command *command, t_args *args)
{
	t_args		*current;
	int			i;

	current = args;
	i = 0;
	command->heredoc_delimiters = malloc(2 * sizeof(char *));
	if (command->heredoc_delimiters == NULL)
		return (false);
	command->heredoc_delimiters[0] = NULL;
	while (current != NULL)
	{
		if (current->prev != NULL && current->prev->value \
		!= NULL && ft_strcmp(current->prev->value, "<<") == 0)
		{
			if (!realloc_temp(command, i))
				return (false);
			command->heredoc_delimiters[i] = ft_strdup(current->value);
			i++;
			command->heredoc_delimiters[i] = NULL;
		}
		current = current->next;
	}
	return (true);
}

void	process_delimiter(char *delimiter)
{
	char	*src;
	char	*dst;
	bool	in_single_quote;
	bool	in_double_quote;

	src = delimiter;
	dst = delimiter;
	in_single_quote = false;
	in_double_quote = false;
	while (*src)
	{
		quote_status(&in_single_quote, &in_double_quote, *src);
		if ((*src != '\'' || in_double_quote) && \
		(*src != '\"' || in_single_quote))
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

void	remove_quotes_in_delimiter(t_command *command)
{
	t_command	*current;
	int			i;

	current = command;
	while (current != NULL)
	{
		if (current->heredoc_delimiters == NULL)
		{
			current = current->next;
			continue ;
		}
		i = 0;
		while (current->heredoc_delimiters[i])
		{
			if (current->heredoc_delimiters[i] != NULL)
				process_delimiter(current->heredoc_delimiters[i]);
			i++;
		}
		current = current->next;
	}
}
