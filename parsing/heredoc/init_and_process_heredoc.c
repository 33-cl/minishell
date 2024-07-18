/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_process_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:15:07 by odx               #+#    #+#             */
/*   Updated: 2024/07/17 22:48:24 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*heredoc(char *delimiter, int *error)
{
	int		len;
	char	*result;

	len = ft_strlen(delimiter);
	if (len == 0)
		return (NULL);
	result = read_line_until_delimiter(delimiter, len, error);
	return (result);
}

char	*concat_and_free(char *str, char *newline_str)
{
	char	*result;

	result = ft_strjoin(str, newline_str);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (result);
}

bool	process_heredoc_args(t_args *args, int *error)
{
	char	*heredoc_output;

	while (args != NULL)
	{
		if (args != NULL && args->prev != NULL && args->prev->value \
		!= NULL && ft_strcmp(args->prev->value, "<<") == 0)
		{
			process_delimiter(args->value);
			heredoc_output = heredoc(args->value, error);
			if (!heredoc_output)
				return (false);
			if (args->value)
				free(args->value);
			args->value = ft_strdup(heredoc_output);
			if (!args->value)
				return (free(heredoc_output), *error = 1, false);
			if (ft_strcmp(args->value, "") != 0)
				args->value = concat_and_free(args->value, "\n");
			if (!args->value)
				return (free(heredoc_output), *error = 1, false);
			free(heredoc_output);
		}
		args = args->next;
	}
	return (true);
}

bool	heredoc_init(t_command *command, int *error)
{
	t_command	*current;

	current = command;
	while (current)
	{
		if (!process_heredoc_args(current->args, error))
			return (false);
		current = current->next;
	}
	return (true);
}
