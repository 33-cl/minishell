/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_process_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:15:07 by odx               #+#    #+#             */
/*   Updated: 2024/07/07 15:44:44 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*heredoc(char *delimiter)
{
	int		len;
	char	*result;

	len = ft_strlen(delimiter);
	if (len == 0)
		return (NULL);
	result = read_line_until_delimiter(delimiter, len);
	return (result);
}

bool	process_heredoc_args(t_args *args)
{
	char	*heredoc_output;

	while (args != NULL)
	{
		if (args != NULL && args->prev != NULL && args->prev->value \
		!= NULL && ft_strcmp(args->prev->value, "<<") == 0)
		{
			heredoc_output = heredoc(args->value);
			if (!heredoc_output)
				return (false);
			if (args->value)
				free(args->value);
			args->value = ft_strdup(heredoc_output);
			if (ft_strcmp(args->value, "") != 0)
				args->value = ft_strjoin(args->value, "\n");
			if (!args->value)
				return (free(heredoc_output), false);
			free(heredoc_output);
		}
		args = args->next;
	}
	return (true);
}

bool	heredoc_init(t_command *command)
{
	t_command	*current;

	current = command;
	while (current)
	{
		if (!process_heredoc_args(current->args))
			return (false);
		current = current->next;
	}
	return (true);
}
