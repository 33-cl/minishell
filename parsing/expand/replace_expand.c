/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:48:38 by odx               #+#    #+#             */
/*   Updated: 2024/07/06 16:48:33 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	expand_multi_quoted_arguments(t_args *current_arg, \
t_env *env, int *status)
{
	if (current_arg->multi_quoted_args != NULL)
		expand_multi_quoted_args(current_arg, env, status);
}

t_command	*replace_expand(t_command *command, t_env *env, int *status, \
int *error)
{
	t_command	*current;
	t_args		*current_arg;
	char		*expanded;

	current = command;
	while (current != NULL)
	{
		current_arg = current->args;
		while (current_arg != NULL)
		{
			if (current_arg->quotes == 0 || (current_arg->prev && \
			current_arg->quotes == 2 && \
			ft_strcmp(current_arg->prev->value, "<<") != 0))
			{
				expanded = expand_argument_value(current_arg, env, status);
				handle_expanded_value(current, current_arg, expanded, error);
				if (*error)
					return (command);
			}
			expand_multi_quoted_arguments(current_arg, env, status);
			current_arg = current_arg->next;
		}
		current = current->next;
	}
	return (command);
}
