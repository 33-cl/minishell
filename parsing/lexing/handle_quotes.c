/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:07:30 by odx               #+#    #+#             */
/*   Updated: 2024/07/06 23:53:23 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	handle_opening_quote(t_handle_quote_params *params)
{
	t_args	*new_arg;

	if (params->iter->i > params->iter->start)
	{
		new_arg = create_new_arg(params->str, params->iter->start, \
		params->iter->i - params->iter->start);
		if (new_arg == NULL)
			return (false);
		add_arg_to_arg(new_arg, &params->args_params->last, \
		params->args_params->args);
	}
	params->iter->current_quote = params->str[params->iter->i];
	params->iter->in_quotes = true;
	params->iter->start = params->iter->i + 1;
	return (true);
}

bool	handle_closing_quote(t_handle_quote_params *params)
{
	t_args	*new_arg;

	new_arg = create_new_arg(params->str, params->iter->start, \
	params->iter->i - params->iter->start);
	if (new_arg == NULL)
		return (false);
	if (params->iter->current_quote == '\'')
		new_arg->quotes = 1;
	else if (params->iter->current_quote == '\"')
		new_arg->quotes = 2;
	add_arg_to_arg(new_arg, &params->args_params->last, \
	params->args_params->args);
	params->iter->in_quotes = false;
	params->iter->start = params->iter->i + 1;
	return (true);
}

bool	handle_quotes(char *str, t_handle_quote_params *quote_params, \
t_iter_params *iter)
{
	if (str[iter->i] == '\'' || str[iter->i] == '\"')
	{
		if (!iter->in_quotes)
		{
			if (!handle_opening_quote(quote_params))
				return (false);
		}
		else if (str[iter->i] == iter->current_quote)
		{
			if (!handle_closing_quote(quote_params))
				return (false);
		}
	}
	return (true);
}

void	update_quote_status(char current_char, bool *in_single_quote, \
bool *in_double_quote)
{
	if (current_char == '\'' && !*in_double_quote && \
	!*in_single_quote)
		*in_single_quote = !*in_single_quote;
	else if (current_char == '\"' && !*in_single_quote && \
	!*in_double_quote)
		*in_double_quote = !*in_double_quote;
}

int	determine_quote_type(const char *token)
{
	bool	in_single_quote;
	bool	in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	while (*token)
	{
		update_quote_status(*token, &in_single_quote, \
		&in_double_quote);
		token++;
	}
	if (in_single_quote)
		return (1);
	else if (in_double_quote)
		return (2);
	else
		return (0);
}
