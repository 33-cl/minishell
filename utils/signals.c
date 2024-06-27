/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:39:25 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/26 18:07:22 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

bool	check_signal(int *status)
{
	if (g_signal == INT)
	{
		*status = 130;
		g_signal = 0;
		return (true);
	}
	return (false);
}

void	sigint_handler(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	g_signal = INT;
	rl_done = 1;
}

void	sigquit_handler(int sig)
{
	(void)sig;
	write(2, "Quit (core dumped)\n", 19);
	signal(SIGQUIT, SIG_DFL);
	kill(getpid(), SIGQUIT);
}