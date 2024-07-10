/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:24:47 by odx               #+#    #+#             */
/*   Updated: 2024/07/05 13:20:09 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_arg_to_arg(t_args *new_arg, t_args **last_arg, t_args *current)
{
	if (*last_arg)
		(*last_arg)->next = new_arg;
	new_arg->prev = *last_arg;
	new_arg->next = NULL;
	if (!current->multi_quoted_args)
		current->multi_quoted_args = new_arg;
	*last_arg = new_arg;
}

void	add_arg_to_list(t_args *new_arg, t_args **last_arg, t_command *current)
{
	if (*last_arg)
		(*last_arg)->next = new_arg;
	new_arg->prev = *last_arg;
	new_arg->next = NULL;
	if (!current->args)
		current->args = new_arg;
	*last_arg = new_arg;
}
