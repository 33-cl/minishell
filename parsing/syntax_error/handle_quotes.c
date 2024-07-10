/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:52:25 by odx               #+#    #+#             */
/*   Updated: 2024/07/05 13:52:50 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
