/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:21:46 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/25 21:12:48 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*si le delimiter heredoc est entre double guillemets j'expand il ne faut pas 
si j'ai le delimiter entre quote je n'expand pas mais moi je vire le dollard 
alors que je devrais le garder
ok > $yes < ok > $yes < $yes < $HOME > $yes
probleme ici je print 2x home

faire les free de clear history*/

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

char	*expand_variables(char *input, t_env *env, t_args *arg, int *status)
{
	t_expand	exp;

	if (!init_expand(&exp, input, env))
		return (NULL);
	while (exp.input[exp.pos] != '\0')
	{
		if (exp.input[exp.pos] == '$')
		{
			if (!process_non_variable_part(&exp))
				return (free(exp.result), NULL);
			if (!process_variable_part(&exp, arg, status))
				return (free(exp.result), NULL);
			exp.start = exp.pos;
		}
		else
			exp.pos++;
	}
	if (!process_non_variable_part(&exp))
		return (free(exp.result), NULL);
	if (env)
		env->exp_result = exp;
	return (exp.result);
}

char	*expand_argument_value(t_args *arg, t_env *env, int *status)
{
	return (expand_variables(arg->value, env, arg, status));
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
			expanded = expand_argument_value(current_multi_quoted_arg, \
			env, status);
			free(current_multi_quoted_arg->value);
			current_multi_quoted_arg->value = expanded;
		}
		current_multi_quoted_arg = current_multi_quoted_arg->next;
	}
}

void	free_argument(t_args *arg)
{
	free(arg->value);
	free(arg);
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
	free_argument(arg);
	return (next_arg);
}

void	handle_expanded_value(t_command *command, t_args *arg, char *expanded, \
int *error)
{
	if (expanded == NULL)
	{
		*error = 1;
		return ;
	}
	if ((ft_strcmp(expanded, "") == 0 && arg == command->args) || \
	(ft_strcmp(expanded, "") == 0 && arg->prev && arg->prev->type != 3 && \
	arg->prev->type != 4))
		arg = remove_empty_argument(command, arg);
	else
	{
		free(arg->value);
		arg->value = expanded;
	}
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
			if (current_arg->multi_quoted_args != NULL)
				expand_multi_quoted_args(current_arg, env, status);
			current_arg = current_arg->next;
		}
		current = current->next;
	}
	return (command);
}
