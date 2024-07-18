/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:25:01 by odx               #+#    #+#             */
/*   Updated: 2024/07/16 13:56:32 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	need_add_spaces_redir(bool in_single_quote, bool in_double_quote, \
char *input, int i)
{
	if (in_double_quote || in_single_quote)
		return (false);
	if (input[i + 1] == '|' || (i >= 1 && input[i] == '|'))
		return (true);
	if (i >= 1 && input[i] == '>' && input[i - 1] == '>')
		if (input[i + 1] != ' ')
			return (true);
	if (i >= 2 && input[i] == '<' && input[i - 1] == '<' && input[i - 2] == '<')
		if (input[i + 1] != ' ')
			return (true);
	return (false);
}

bool	need_add_spaces(bool in_single_quote, bool in_double_quote, \
char *input, int i)
{
	if (in_double_quote || in_single_quote)
		return (false);
	if (i > 0 && (((input[i + 1] == '>' && input[i] != '>') || \
	(input[i + 1] == '<' && input[i] != '<') || input[i + 1] == '|') && \
	input[i] != ' '))
		return (true);
	return (false);
}

void	handle_space_insertion(char *input, char *new_str, \
t_space_insertion_params *params)
{
	if (need_add_spaces(params->in_single_quote, params->in_double_quote, \
	input, params->i))
		new_str[params->len++] = ' ';
	if (need_add_spaces_redir(params->in_single_quote, \
	params->in_double_quote, new_str, params->len))
		new_str[params->len++] = ' ';
	if (!params->in_single_quote && !params->in_double_quote && \
	input[params->i] == '>' && input[params->i + 1] != '>' && \
	input[params->i + 1] != ' ')
		new_str[params->len++] = ' ';
	if (!params->in_single_quote && !params->in_double_quote && \
	input[params->i] == '<' && input[params->i + 1] != '<' && \
	input[params->i + 1] != ' ')
		new_str[params->len++] = ' ';
	if (!params->in_single_quote && !params->in_double_quote && \
	input[params->i + 1] && input[params->i + 1] == '|' && \
	input[params->i] != ' ')
		new_str[params->len++] = ' ';
	if (!params->in_single_quote && !params->in_double_quote && \
	input[params->i] == '|' && input[params->i + 1] != ' ' && \
	input[params->i + 1] != '\0')
		new_str[params->len++] = ' ';
}

void	check_and_insert_space(char *input, char *new_str, \
t_space_insertion_params *params)
{
	if (!params->in_single_quote && !params->in_double_quote)
	{
		if (input[params->i] == '>' && input[params->i + 1] == '>')
		{
			new_str[params->len++] = '>';
			new_str[params->len++] = '>';
			new_str[params->len++] = ' ';
			params->i += 1;
		}
		else if (input[params->i] == '<' && input[params->i + 1] == '<')
		{
			new_str[params->len++] = '<';
			new_str[params->len++] = '<';
			new_str[params->len++] = ' ';
			params->i += 1;
		}
		else
			new_str[params->len++] = input[params->i];
	}
	else
		new_str[params->len++] = input[params->i];
}

char	*put_space_before_redir(char *input, int i)
{
	char						*new_str;
	t_space_insertion_params	params;

	new_str = realloc_and_init(input, &params.in_single_quote, \
	&params.in_double_quote);
	if (!new_str)
		return (NULL);
	params.i = i;
	params.len = 0;
	while (input[++params.i])
	{
		quote_status(&params.in_single_quote, \
		&params.in_double_quote, input[params.i]);
		check_and_insert_space(input, new_str, &params);
		handle_space_insertion(input, new_str, &params);
	}
	new_str[params.len] = '\0';
	free(input);
	return (new_str);
}
