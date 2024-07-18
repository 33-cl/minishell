/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:39:25 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/18 16:46:12 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	g_signal = INT;
	rl_done = 1;
}

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	g_signal = INT;
	rl_done = 1;
}

void	sigint_handler_child(int sig)
{
	(void)sig;
	printf("\n");
	g_signal = INT_C;
	rl_done = 1;
}

void	sigquit_handler(int sig)
{
	(void)sig;
	write(2, "Quit (core dumped)\n", 19);
	g_signal = QUIT;
	rl_done = 1;
}
