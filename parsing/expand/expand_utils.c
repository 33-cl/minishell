/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:21:46 by qordoux           #+#    #+#             */
/*   Updated: 2024/07/17 20:32:40 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	init_expand(t_expand *exp, char *input, t_env *env)
{
	exp->input = input;
	exp->env = env;
	exp->result_size = ft_strlen(input) + 1;
	exp->result = malloc(sizeof(char) * exp->result_size + 1);
	if (exp->result == NULL)
		return (false);
	exp->result[0] = '\0';
	exp->pos = 0;
	exp->start = 0;
	return (true);
}

char	*handle_dollar_sign(char *input, t_args *arg)
{
	if ((ft_strcmp(input, "$") == 0 && !arg->next))
		return (ft_strdup("$"));
	if (ft_strcmp(input, "$") == 0 && (arg->quotes == 0 || arg->quotes == -1) \
	&& arg->next && (arg->next->quotes == 2 || arg->next->quotes == 1))
		return (ft_strdup(input));
	return (NULL);
}

t_args	*remove_empty_argument(t_command *command, t_args *arg)
{
	t_args	*next_arg;

	next_arg = arg->next;
	if (arg->prev != NULL)
		arg->prev->next = arg->next;
	if (arg->next != NULL)
		arg->next->prev = arg->prev;
	if (arg == command->args)
		command->args = arg->next;
	free(arg->value);
	return (next_arg);
}

bool	handle_expanded_value(t_command *command, t_args *arg, char *expanded, \
int *error)
{
	if (expanded == NULL)
	{
		*error = 1;
		return (true);
	}
	if ((ft_strcmp(expanded, "") == 0 && arg == command->args) || \
	(ft_strcmp(expanded, "") == 0 && arg->prev && arg->prev->type != 3 && \
	arg->prev->type != 4))
	{
		arg = remove_empty_argument(command, arg);
		return (false);
	}
	else
	{
		free(arg->value);
		arg->value = ft_strdup(expanded);
	}
	return (true);
}

void	expand_multi_quoted_args(t_args *arg, t_env *env, int *status)
{
	t_args	*current_multi_quoted_arg;
	char	*expanded;

	current_multi_quoted_arg = arg->multi_quoted_args;
	while (current_multi_quoted_arg != NULL)
	{
		if (current_multi_quoted_arg->quotes != 1)
		{
			expanded = expand_argument_value_multi(current_multi_quoted_arg, \
			env, status);
			free(current_multi_quoted_arg->value);
			current_multi_quoted_arg->value = expanded;
		}
		current_multi_quoted_arg = current_multi_quoted_arg->next;
	}
}
