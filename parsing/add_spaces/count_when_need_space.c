/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_when_need_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:28:02 by qordoux           #+#    #+#             */
/*   Updated: 2024/07/11 11:26:42 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	quote_status(bool *in_single_quote, bool *in_double_quote, \
char current_char)
{
	if (!*in_double_quote && current_char == '\'')
		*in_single_quote = !*in_single_quote;
	else if (!*in_single_quote && current_char == '\"')
		*in_double_quote = !*in_double_quote;
}
