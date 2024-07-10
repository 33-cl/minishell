/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_final_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:59:21 by odx               #+#    #+#             */
/*   Updated: 2024/07/07 15:05:23 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	init_main_vars(t_command *command, t_args **current, \
t_cmd **head_final_list, t_cmd **current_final)
{
	*current = command->args;
	*head_final_list = NULL;
	*current_final = NULL;
	if (!init_new_final_list_node(head_final_list, current_final, command))
		return (false);
	(*current_final)->i = 0;
	(*current_final)->j = 0;
	return (true);
}

bool	main_loop(t_command *command, t_args **current, \
t_cmd **head_final_list, t_cmd **current_final)
{
	int	return_value;

	while (*current != NULL)
	{
		if ((*current)->type == 2 && (*current)->quotes == 0)
		{
			if (!handle_new_final_node(head_final_list, current_final, command))
				return (false);
			*current = (*current)->next;
			continue ;
		}
		return_value = handle_current_element(current, current_final);
		if (return_value == 0)
			continue ;
		else if (return_value == 1)
			return (free_final_list(head_final_list), false);
		if (!process_current(*current, *current_final, command))
			return (free_final_list(head_final_list), false);
		*current = (*current)->next;
	}
	if (*current_final != NULL && (*current_final)->args != NULL)
		(*current_final)->args[(*current_final)->i] = NULL;
	return (true);
}

bool	put_everything_in_final_list(t_command *command)
{
	t_args	*current;
	t_cmd	*head_final_list;
	t_cmd	*current_final;

	if (!init_main_vars(command, &current, &head_final_list, &current_final))
		return (false);
	if (!main_loop(command, &current, &head_final_list, &current_final))
		return (false);
	command->final_cmd = head_final_list;
	return (true);
}
