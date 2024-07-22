/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:51:46 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:24 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_signals_n_reset(int *status, char **input, int *old_status)
{
	(void)status;
	*old_status = *status;
	if (*input)
		free(*input);
	*input = NULL;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (false);
}

bool	check_signal(int *status)
{
	if (g_signal == INT_C)
	{
		*status = 130;
		g_signal = 0;
		return (true);
	}
	else if (g_signal == QUIT)
	{
		*status = 131;
		g_signal = 0;
		return (true);
	}
	else if (g_signal == INT)
	{
		*status = 130;
		g_signal = 0;
		return (true);
	}
	return (false);
}
