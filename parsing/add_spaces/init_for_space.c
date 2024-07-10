/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_for_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:41:05 by odx               #+#    #+#             */
/*   Updated: 2024/07/05 11:42:59 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*initialize_params(char *input, t_space_insertion_params *params, int i)
{
	bool	in_single_quote;
	bool	in_double_quote;
	char	*new_str;

	new_str = realloc_and_init(input, &in_single_quote, &in_double_quote);
	if (!new_str)
		return (NULL);
	params->i = i;
	params->len = 0;
	params->in_single_quote = in_single_quote;
	params->in_double_quote = in_double_quote;
	return (new_str);
}
