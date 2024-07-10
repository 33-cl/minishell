/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_new_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:04:53 by odx               #+#    #+#             */
/*   Updated: 2024/07/05 12:05:18 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_iter_params(t_iter_params *iter)
{
	iter->i = 0;
	iter->start = 0;
	iter->in_quotes = false;
	iter->current_quote = 0;
}

void	init_args_params(t_args_params *args_params, t_args *args)
{
	args_params->args = args;
	args_params->last = NULL;
}

void	init_handle_quote_params(t_handle_quote_params *quote_params, \
char *str, t_iter_params *iter, t_args_params *args_params)
{
	quote_params->str = str;
	quote_params->iter = iter;
	quote_params->args_params = args_params;
}
