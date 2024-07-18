/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:03:47 by odx               #+#    #+#             */
/*   Updated: 2024/07/13 23:11:25 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	handle_new_final_node(t_cmd **head_final_list, \
t_cmd **current_final, t_command *command)
{
	if (!init_new_final_list_node(head_final_list, current_final, command))
		return (false);
	(*current_final)->i = 0;
	(*current_final)->j = 0;
	return (true);
}

bool	process_specifier_args(t_args **current, t_cmd **current_final, int *j)
{
	add_specifier_to_struct(current_final, *current, j);
	*current = (*current)->next;
	if (*current != NULL && (*current)->type != 3)
		*current = (*current)->next;
	return (true);
}

bool	handle_delimiter_final(t_args **current, t_cmd **current_final, int *j)
{
	while ((*current)->quotes == 0 && (ft_strcmp((*current)->value, "<<") == 0 \
	|| ft_strcmp((*current)->value, ">>") == 0 || ft_strcmp((*current)->value, \
	"<") == 0 || ft_strcmp((*current)->value, ">") == 0))
	{
		process_specifier_args(&(*current), &(*current_final), &(*j));
		return (true);
	}
	return (false);
}

int	handle_current_element(t_args **current, t_cmd **current_final)
{
	if (handle_delimiter_final(current, current_final, &(*current_final)->j))
	{
		if ((*current_final)->malloc_failed == true)
			return (1);
		return (0);
	}
	return (2);
}

bool	process_current(t_args *current, t_cmd *current_final, \
t_command *command)
{
	if (current->type != 3 || (current->prev && current->prev->type != 3))
	{
		command->malloc_error = process_quoted_or_unquoted(current, \
		current_final, &current_final->i);
		if (command->malloc_error == 2)
			return (false);
	}
	return (true);
}
