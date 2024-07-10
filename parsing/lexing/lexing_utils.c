/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:40:40 by odx               #+#    #+#             */
/*   Updated: 2024/07/05 13:45:15 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_quote(char c, char *last_quote, int *in_quotes, int *count)
{
	if (*in_quotes && c == *last_quote)
		*in_quotes = 0;
	else if (!*in_quotes)
	{
		*in_quotes = 1;
		*last_quote = c;
		(*count)++;
	}
}

bool	realloc_temp(t_command *command, int i)
{
	char	**temp;
	size_t	new_size;
	size_t	old_size;

	old_size = sizeof(char *) * (i + 1);
	new_size = sizeof(char *) * (i + 2);
	temp = ft_realloc_old_size_bis(command->heredoc_delimiters, \
	old_size, new_size);
	if (temp == NULL)
		return (false);
	command->heredoc_delimiters = temp;
	return (true);
}
