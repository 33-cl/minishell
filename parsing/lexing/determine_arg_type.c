/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_arg_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:18:33 by odx               #+#    #+#             */
/*   Updated: 2024/07/05 13:42:54 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	determine_arg_type(char *token, t_args *new_arg, \
t_args *last_arg, int i)
{
	new_arg->quotes = determine_quote_type(token);
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "\'|\'") == 0 || \
	ft_strcmp(token, "\"|\"") == 0)
		new_arg->type = T_PIPE;
	else if (ft_strcmp(token, "<<") == 0)
		new_arg->type = T_HEREDOC;
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0 || \
	ft_strcmp(token, ">>") == 0)
		new_arg->type = T_REDIR;
	else if (i == 0)
		new_arg->type = T_CMD;
	else
		new_arg->type = T_ARG;
	new_arg->prev = last_arg;
	new_arg->next = NULL;
}
