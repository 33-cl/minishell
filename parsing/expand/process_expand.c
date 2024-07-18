/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:24:29 by odx               #+#    #+#             */
/*   Updated: 2024/07/15 18:02:44 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* append to result rellocate result if result need space and calculate 
length tu use strlcat to append temp to result */

bool	append_to_result(t_expand *exp, char *temp)
{
	size_t	temp_len;

	temp_len = ft_strlen(temp);
	if (!exp->result)
		return (false);
	if (exp->result_size < ft_strlen(exp->result) + temp_len + 1)
	{
		exp->result_size = ft_strlen(exp->result) + temp_len + 1;
		exp->result = ft_realloc_old_size(exp->result, ft_strlen(exp->result) \
		+ 1, exp->result_size);
		if (exp->result == NULL)
			return (false);
	}
	ft_strlcat(exp->result, temp, exp->result_size);
	return (true);
}

bool	process_non_variable_part(t_expand *exp)
{
	char	*temp;
	bool	succes;

	if (exp->start < exp->pos)
	{
		temp = ft_strndup(exp->input + exp->start, exp->pos - exp->start);
		if (temp == NULL)
			return (false);
		succes = append_to_result(exp, temp);
		free(temp);
		return (succes);
	}
	return (true);
}

bool	handle_special_cases(t_expand *exp, t_args *arg, int *status)
{
	bool	append;

	if (arg->quotes != 1 && exp->input[exp->pos + 1] == '?')
	{
		exp->start = ++exp->pos;
		exp->start = ++exp->pos;
		append = append_to_result_itoa(exp, ft_itoa(*status));
		return (append);
	}
	if ((arg->quotes == 2 && !ft_isalnum(exp->input[exp->pos + 1]) && \
	exp->input[exp->pos + 1] != '_') || exp->input[exp->pos + 1] == '=')
	{
		exp->start = ++exp->pos;
		return (append_to_result(exp, "$"));
	}
	return (false);
}

bool	handle_numeric_variable(t_expand *exp, int *status)
{
	char	*var_value;

	if (ft_isdigit(exp->input[exp->pos]))
	{
		exp->pos++;
		var_value = ft_strndup(exp->input + exp->start, exp->pos \
		- exp->start - 1);
		if (var_value == NULL)
			return (*status = -1, false);
		if (var_value)
		{
			append_to_result(exp, var_value);
			free(var_value);
			return (true);
		}
	}
	return (false);
}

bool	process_variable_part(t_expand *exp, t_args *arg, int *status)
{
	char	*var_name;
	char	*var_value;

	if (handle_special_cases(exp, arg, status))
		return (true);
	exp->start = ++exp->pos;
	if (exp->input[exp->pos - 1] == '$' && (exp->input[exp->pos] == '\0' || \
	exp->input[exp->pos] == '\n'))
		return (append_to_result(exp, "$"), true);
	if (handle_numeric_variable(exp, status))
		return (true);
	while (exp->input[exp->pos] != '\0' && (ft_isalnum(exp->input[exp->pos]) \
	|| exp->input[exp->pos] == '_'))
		exp->pos++;
	var_name = ft_strndup(exp->input + exp->start, exp->pos - exp->start);
	if (var_name == NULL)
		return (*status = -1, false);
	var_value = get_env(&exp->env, var_name);
	free(var_name);
	if (var_value)
		return (append_to_result(exp, var_value), true);
	return (true);
}
