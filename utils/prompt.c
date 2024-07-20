/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:51:41 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/20 23:05:17 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Creates and display the prompt and waiting for user input

	Searching path with getcwd
	/home/maeferre/Desktop/minishell
*/

bool	prompt(int *status, char **input)
{
	char	*prompt;

	*input = NULL;
	prompt = get_prompt(status);
	if (!prompt)
		return (ft_putstr_fd("error : current working directory has been deleted\n", 2),
			*status = 1, false);
	*input = readline(prompt);
	if (*input && !strcmp(*input, "\0"))
		return (free(prompt), false);
	add_history(*input);
	free(prompt);
	return (true);
}

char	*get_prompt(int *status)
{
	char	*command;
	char	*cwd;
	char	*final_cwd;

	(void)status;
	if (*status == 0)
		command = ft_strdup("\001\033[0;32m\002♦ \001\033[1;35m\002");
	else
		command = ft_strdup("\001\033[0;31m\002♦ \001\033[1;35m\002");
	if (!command)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(command), NULL);
	final_cwd = ft_strdup(ft_strrchr(cwd, '/') + 1);
	free(cwd);
	if (!final_cwd)
		return (free(command), NULL);
	command = ft_strjoin_free(command, final_cwd, 3);
	if (!command)
		return (free(command), free(final_cwd), NULL);
	command = ft_strjoin_free(command, " \001\033[0m\002", 1);
	if (!command)
		return (free(final_cwd), NULL);
	return (command);
}

bool	skip_first_rl(void)
{
	int		fds[2];
	int		stdin_copy;
	char	*input;

	pipe(fds);
	write(fds[1], "\n", 1);
	close(fds[1]);
	stdin_copy = dup(STDIN_FILENO);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (false);
	input = readline("");
	free(input);
	if (dup2(stdin_copy, STDIN_FILENO) == -1)
		return (false);
	close(fds[0]);
	close(stdin_copy);
	return (true);
}
