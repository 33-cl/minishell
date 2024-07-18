/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:48:38 by odx               #+#    #+#             */
/*   Updated: 2024/07/13 21:55:51 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	expand_multi_quoted_arguments(t_args *current_arg, \
t_env *env, int *status)
{
	if (current_arg->multi_quoted_args != NULL)
		expand_multi_quoted_args(current_arg, env, status);
}

bool	handle_expansion_result(t_command *current, t_args **current_arg, \
char *expanded, int *error)
{
	t_args	*temp;

	if (!handle_expanded_value(current, *current_arg, expanded, error))
	{
		temp = *current_arg;
		*current_arg = (*current_arg)->next;
		free(temp);
	}
	else
		(*current_arg) = (*current_arg)->next;
	if (*error)
		return (false);
	if (ft_strcmp(expanded, "") != 0)
		free(expanded);
	return (true);
}

void	handle_expansion_multi(t_args **current_arg, t_env *env, int *status)
{
	expand_multi_quoted_arguments(*current_arg, env, status);
	*current_arg = (*current_arg)->next;
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
				if (!handle_expansion_result(current, &current_arg, expanded, \
				error))
					return (command);
			}
			else
				handle_expansion_multi(&current_arg, env, status);
		}
		current = current->next;
	}
	return (command);
}

bool	append_to_result_itoa(t_expand *exp, char *temp)
{
	size_t	temp_len;

	temp_len = ft_strlen(temp);
	if (exp->result_size < ft_strlen(exp->result) + temp_len + 1)
	{
		exp->result_size = ft_strlen(exp->result) + temp_len + 1;
		exp->result = ft_realloc_old_size(exp->result, ft_strlen(exp->result) \
		+ 1, exp->result_size);
		if (exp->result == NULL)
			return (false);
	}
	ft_strlcat(exp->result, temp, exp->result_size);
	free(temp);
	return (true);
}
