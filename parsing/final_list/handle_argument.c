/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:19:06 by odx               #+#    #+#             */
/*   Updated: 2024/07/15 14:38:07 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_unquoted_args(t_args *current, t_cmd *current_final, int *i)
{
	int	result;

	if (current->type == 0)
	{
		result = duplicate_cmd(current, current_final);
		if (result != 0)
			return (result);
	}
	result = realloc_args_array(current, current_final);
	if (result != 0)
		return (result);
	if (current->quotes != 0 && (current->prev == NULL || \
	ft_strcmp(current->prev->value, "<<") != 0))
	{
		result = process_quoted_arg(current, current_final, i);
		if (result != 0)
			return (result);
	}
	else
	{
		result = process_unquoted_arg(current, current_final, i);
		if (result != 0)
			return (result);
	}
	return (0);
}

bool	process_multi_quoted_args(t_args *current, t_cmd *current_final, int *i)
{
	t_args	*current_multi_quoted_args;

	current_multi_quoted_args = current->multi_quoted_args;
	if (!handle_multi_quoted_args(current_multi_quoted_args, current_final, i))
		return (false);
	return (true);
}

int	process_quoted_or_unquoted(t_args *current, t_cmd *current_final, int *i)
{
	if ((!current->prev && current->type != 3) || (current->prev \
	&& current->prev->type != 3))
	{
		if (current->multi_quoted_args)
		{
			if (!(process_multi_quoted_args(current, current_final, &(*i))))
				return (2);
		}
		else
		{
			if (process_unquoted_args(current, current_final, &(*i)) == 2)
				return (2);
		}
	}
	return (0);
}
