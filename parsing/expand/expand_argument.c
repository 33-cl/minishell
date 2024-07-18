/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:13:09 by odx               #+#    #+#             */
/*   Updated: 2024/07/13 22:24:31 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_expansion(t_expand *exp, t_args *arg, int *status)
{
	if (!process_non_variable_part(exp))
		return (0);
	if (!process_variable_part(exp, arg, status))
		return (0);
	exp->start = exp->pos;
	return (1);
}

char	*expand_variables(char *input, t_env *env, t_args *arg, int *status)
{
	t_expand	exp;
	char		*result;

	if (!init_expand(&exp, input, env))
		return (NULL);
	result = handle_dollar_sign(input, arg);
	if (result)
		return (free(exp.result), result);
	while (exp.input[exp.pos] != '\0')
	{
		if (exp.input[exp.pos] == '$')
		{
			if (!process_expansion(&exp, arg, status))
				return (free(exp.result), NULL);
		}
		else
			exp.pos++;
	}
	if (!process_non_variable_part(&exp))
		return (free(exp.result), NULL);
	if (env)
		env->exp_result = exp;
	if (exp.result && ft_strcmp(exp.result, "") == 0)
		return (free(exp.result), "");
	return (exp.result);
}

char	*expand_argument_value(t_args *arg, t_env *env, int *status)
{
	return (expand_variables(arg->value, env, arg, status));
}

char	*expand_variables_multi(char *input, t_env *env, \
t_args *arg, int *status)
{
	t_expand	exp;
	char		*result;

	if (!init_expand(&exp, input, env))
		return (NULL);
	result = handle_dollar_sign(input, arg);
	if (result)
		return (free(exp.result), result);
	while (exp.input[exp.pos] != '\0')
	{
		if (exp.input[exp.pos] == '$')
		{
			if (!process_expansion(&exp, arg, status))
				return (free(exp.result), NULL);
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

char	*expand_argument_value_multi(t_args *arg, t_env *env, int *status)
{
	return (expand_variables_multi(arg->value, env, arg, status));
}
