/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:30:32 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/25 21:34:20 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*ok > $HOME < $PATH > $YES > OUI < NON | OUI
maybe ajouter un \n a la fin du contenu heredoc sauf si il est vide 
->voir avec mael*/

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

bool	handle_new_final_node(t_cmd **head_final_list, \
t_cmd **current_final, t_command *command)
{
	if (!init_new_final_list_node(head_final_list, current_final, command))
		return (false);
	(*current_final)->i = 0;
	(*current_final)->j = 0;
	return (true);
}

bool	handle_current_element(t_args **current, t_cmd **current_final)
{
	if (handle_delimiter_final(current, current_final, &(*current_final)->j))
	{
		if ((*current_final)->malloc_failed == true)
			return (false);
		return (true);
	}
	return (false);
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

bool	main_loop(t_command *command, t_args **current, \
t_cmd **head_final_list, t_cmd **current_final)
{
	while (*current != NULL)
	{
		if ((*current)->type == 2 && (*current)->quotes == 0)
		{
			if (!handle_new_final_node(head_final_list, current_final, command))
				return (false);
			*current = (*current)->next;
			continue ;
		}
		if (handle_current_element(current, current_final))
			continue ;
		if (!process_current(*current, *current_final, command))
		{
			free_final_list(head_final_list);
			return (false);
		}
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
