/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:21:46 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/12 17:23:48 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//si le delimiter heredoc est entre double guillemets j'expand il ne faut pas

bool	init_expand(t_expand *exp, char *input, t_env *env)
{
	exp->input = input;
	exp->env = env;
	exp->result_size = ft_strlen(input) + 1;
	exp->result = malloc(sizeof(char) * exp->result_size + 1); // mal securise
	if (exp->result == NULL)
		return (false);
	exp->result[0] = '\0';
	exp->pos = 0;
	exp->start = 0;
	
	return (true);
}

char	*expand_variables(char *input, t_env *env, t_args *arg)
{
	t_expand	exp;

	if (!init_expand(&exp, input, env))
		return (NULL);
	while (exp.input[exp.pos] != '\0')
	{
		if (exp.input[exp.pos] == '$')
		{
			if (!process_non_variable_part(&exp))
			{
				free(exp.result);
				return(NULL);
			}
			if (!process_variable_part(&exp, arg))
			{
				free(exp.result);
				return(NULL);
			}
			exp.start = exp.pos;
		}
		else
			exp.pos++;
	}
	if (!process_non_variable_part(&exp))
	{
		free(exp.result);
		return (NULL);
	}
	return (exp.result);
}

t_command	*replace_expand(t_command *command, t_env *env)
{
	t_command	*current;
	t_args		*current_multi_quoted_arg;
	t_args		*current_arg;

	current = command;
	//pas besoin de parcourir current imo
	while (current != NULL)
	{
		current_arg = current->args;
		while (current_arg != NULL)
		{
			current_multi_quoted_arg = current_arg->multi_quoted_args;
			if (current_arg->quotes == 0 || (current_arg->prev && current_arg->quotes == 2 && ft_strcmp(current_arg->prev->value, "<<") != 0))
				current_arg->value = expand_variables(current_arg->value, env, current_arg);
			if (current_arg->multi_quoted_args != NULL)
			{
				while (current_multi_quoted_arg != NULL)
				{
					if (current_multi_quoted_arg->quotes != 1)//quotes pas initialise
						current_multi_quoted_arg->value = expand_variables(current_multi_quoted_arg->value, env, current_multi_quoted_arg);
					current_multi_quoted_arg = current_multi_quoted_arg->next;
				}
			}
			current_arg = current_arg->next;
		}
		current = current->next;
	}
	return (command);
}
