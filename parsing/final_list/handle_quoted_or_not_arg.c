/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quoted_or_not_arg.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:34:47 by odx               #+#    #+#             */
/*   Updated: 2024/07/07 00:33:21 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	update_current_final(t_cmd *current_final, char *temp, int *i)
{
	current_final->args[*i] = temp;
	(*i)++;
	current_final->args[*i] = NULL;
	if (current_final->cmd)
		free(current_final->cmd);
	current_final->cmd = ft_strdup(current_final->args[0]);
	if (current_final->cmd == NULL)
		return (false);
	return (true);
}

bool	handle_single_quoted_arg(t_args *current_multi_quoted_args, char **temp)
{
	char	*new_str;
	char	*new_temp;

	new_str = ft_strdup(current_multi_quoted_args->value);
	if (new_str == NULL)
	{
		free(*temp);
		return (false);
	}
	new_temp = concatenate_strings(*temp, new_str);
	if (new_temp == NULL)
	{
		free_two_strings(*temp, new_str);
		return (false);
	}
	free(*temp);
	*temp = new_temp;
	free(new_str);
	return (true);
}

bool	handle_multi_quoted_args(t_args *current_multi_quoted_args, \
t_cmd *current_final, int *i)
{
	char	*temp;

	temp = ft_strdup("");
	if (temp == NULL)
		return (false);
	while (current_multi_quoted_args != NULL)
	{
		if (!handle_single_quoted_arg(current_multi_quoted_args, &temp))
			return (false);
		current_multi_quoted_args = current_multi_quoted_args->next;
	}
	if (!update_current_final(current_final, temp, i))
		return (false);
	return (true);
}
