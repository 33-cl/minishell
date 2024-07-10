/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:53:24 by odx               #+#    #+#             */
/*   Updated: 2024/07/05 13:43:06 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	split_into_new_nodes(char *str, t_args *args)
{
	t_iter_params			iter;
	t_args_params			args_params;
	t_handle_quote_params	quote_params;

	init_iter_params(&iter);
	init_args_params(&args_params, args);
	init_handle_quote_params(&quote_params, str, &iter, &args_params);
	args->multi_quoted_args = NULL;
	while (str[iter.i])
	{
		if (!handle_quotes(str, &quote_params, &iter))
			return (false);
		iter.i++;
	}
	if (!create_and_add_remaining_arg(str, &iter, &args_params))
		return (false);
	return (true);
}

int	count_nodes(char *str)
{
	int		count;
	int		i;
	char	last_quote;
	int		in_quotes;

	count = 0;
	i = 0;
	last_quote = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			handle_quote(str[i], &last_quote, &in_quotes, &count);
		else if (!in_quotes && (i == 0 || str[i - 1] == last_quote))
			count++;
		i++;
	}
	return (count);
}

bool	split_for_multi_quoted(char *str, t_args *args)
{
	int	nb_words;

	nb_words = count_nodes(str);
	if (nb_words > 1)
		split_into_new_nodes(str, args);
	return (true);
}

bool	process_argument(char *token, t_command *command, \
t_args **last_arg, t_command *current)
{
	t_args	*new_arg;

	new_arg = init_new_arg(token);
	if (!new_arg)
		return (false);
	if (ft_strcmp(new_arg->value, "<<") == 0)
		command->nb_heredocs++;
	split_for_multi_quoted(new_arg->value, new_arg);
	if (!new_arg->value)
	{
		free(new_arg);
		return (false);
	}
	determine_arg_type(token, new_arg, *last_arg, command->index);
	add_arg_to_list(new_arg, last_arg, current);
	return (true);
}

bool	parse_and_fill_struct(t_command *command, char *segment)
{
	char		*token;
	t_args		*last_arg;
	t_command	*current;

	last_arg = NULL;
	token = ft_strtok_space(segment);
	current = command;
	command->index = 0;
	while (token != NULL)
	{
		if (!process_argument(token, command, &last_arg, current))
			return (false);
		token = ft_strtok_space(NULL);
		command->index++;
	}
	return (true);
}
