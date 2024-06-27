/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:28:02 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/25 19:45:22 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*realloc_and_init(char *input, bool *in_single_quote, \
bool *in_double_quote)
{
	char	*new_str;

	*in_single_quote = false;
	*in_double_quote = false;
	new_str = realloc_for_more_space(input, *in_single_quote, *in_double_quote);
	if (!new_str)
	{
		free(input);
		return (NULL);
	}
	return (new_str);
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
	if (input[params->i] == '|' && input[params->i + 1] != ' ' && \
	input[params->i + 1] != '\0')
		new_str[params->len++] = ' ';
}

char	*put_space_before_redir(char *input, int i)
{
	char						*new_str;
	bool						in_single_quote;
	bool						in_double_quote;
	t_space_insertion_params	params;

	new_str = realloc_and_init(input, &in_single_quote, &in_double_quote);
	if (!new_str)
		return (NULL);
	params.i = i;
	params.len = 0;
	params.in_single_quote = in_single_quote;
	params.in_double_quote = in_double_quote;
	while (input[++params.i])
	{
		quote_status(&params.in_single_quote, &params.in_double_quote, \
		input[params.i]);
		new_str[params.len++] = input[params.i];
		handle_space_insertion(input, new_str, &params);
	}
	params.len = ft_strlen(new_str);
	new_str[params.len] = '\0';
	free(input);
	return (new_str);
}

bool	redir_need_space(bool in_single_quote, bool in_double_quote, \
char *input, int i)
{
	if (!in_double_quote && !in_single_quote && (((input[i] == '>' && \
	input[i + 1] != '>') || (input[i] == '<' && input[i + 1] != '<')) && \
	input[i + 1] != ' ') && \
		input[i + 1] != '\0')
		return (true);
	else if (i > 0 && !in_double_quote && !in_single_quote && \
	(((input[i] == '>' && input[i - 1] != '>') || (input[i] == '<' && \
	input[i - 1] != '<')) && input[i - 1] != ' '))
		return (true);
	else if (i >= 1 && !in_double_quote && !in_single_quote && \
	input[i] == '>' && input[i + 1] == '>' && input[i + 2] != ' ')
		return (true);
	if (input[i] == '>' && input[i + 1] != '>' && input[i + 1] != ' ')
		return (true);
	if (input[i] == '<' && input[i + 1] != '<' && input[i + 1] != ' ')
		return (true);
	return (false);
}

bool	pipe_need_space(bool in_single_quote, bool in_double_quote, \
char *input, int i)
{
	if ((input[i] == '|' && input[i + 1] != ' ' && input[i + 1] != '\0') || \
	(i > 0 && input[i] == '|' && input[i - 1] != ' '))
		return (true);
	if (need_add_spaces(in_single_quote, in_double_quote, input, i))
		return (true);
	if (need_add_spaces_redir(in_single_quote, in_double_quote, input, i))
		return (true);
	return (false);
}

bool	count_when_need_space(bool in_single_quote, \
bool in_double_quote, char *input, int i)
{
	if (redir_need_space(in_single_quote, in_double_quote, input, i))
		return (true);
	if (pipe_need_space(in_single_quote, in_double_quote, input, i))
		return (true);
	return (false);
}

char	*realloc_for_more_space(char *input, \
bool in_single_quote, bool in_double_quote)
{
	int			i;
	int			len;
	int			count;
	char		*new_str;

	in_single_quote = false;
	in_double_quote = false;
	count = 0;
	len = ft_strlen(input) + 1;
	i = -1;
	while (input[++i])
	{
		quote_status(&in_single_quote, &in_double_quote, input[i]);
		if (count_when_need_space(in_single_quote, in_double_quote, input, i))
			count += 2;
	}
	new_str = ft_calloc(((len + count) * 2), sizeof(char));
	if (!new_str)
		return (NULL);
	return (new_str);
}
