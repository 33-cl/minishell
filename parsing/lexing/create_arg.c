/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:23:21 by odx               #+#    #+#             */
/*   Updated: 2024/07/05 12:23:23 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_args	*create_new_arg(const char *str, unsigned int start, size_t length)
{
	t_args	*new_arg;

	new_arg = malloc(sizeof(t_args));
	if (!new_arg)
		return (NULL);
	new_arg->quotes = -1;
	new_arg->type = -1;
	new_arg->value = ft_substr(str, start, length);
	if (!new_arg->value)
	{
		free(new_arg);
		return (NULL);
	}
	new_arg->multi_quoted_args = NULL;
	new_arg->next = (NULL);
	new_arg->prev = (NULL);
	return (new_arg);
}

bool	create_and_add_arg(char *str, int start, int end, \
t_args_params *args_params)
{
	t_args	*new_arg;

	new_arg = create_new_arg(str, start, end);
	if (new_arg == NULL)
		return (false);
	add_arg_to_arg(new_arg, &args_params->last, args_params->args);
	return (true);
}

bool	create_and_add_remaining_arg(char *str, t_iter_params *iter, \
t_args_params *args_params)
{
	if (iter->start < iter->i)
	{
		if (!create_and_add_arg(str, iter->start, \
		iter->i - iter->start, args_params))
			return (false);
	}
	return (true);
}

t_args	*init_new_arg(char *token)
{
	t_args	*new_arg;

	new_arg = malloc(sizeof(t_args));
	if (!new_arg)
		return (NULL);
	new_arg->quotes = -1;
	new_arg->type = -1;
	new_arg->multi_quoted_args = NULL;
	new_arg->next = NULL;
	new_arg->prev = NULL;
	new_arg->value = ft_strdup(token);
	if (!new_arg->value)
	{
		free(new_arg);
		return (NULL);
	}
	return (new_arg);
}
