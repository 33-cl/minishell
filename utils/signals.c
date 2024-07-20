/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:51:46 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/19 20:55:49 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_signals(int *status)
{
	(void)status;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	// if (check_signal(status))
	// 	return (true);
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
