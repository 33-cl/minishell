/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:26:30 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/20 00:33:40 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_command *command, char *input)
{
	command->args = ft_split(input, ' ');
	command->cmd = ft_strdup(input);
}

int	loop(char **env)
{
	int			status;
	t_command   command;
	char        *input;

	status = 0;
	while (1)
	{
		input = prompt(status);
		if (!input)
			return (1);
		parsing(&command, input);
		status = execute(&command, env, status);
		ft_free_tab(command.args);
		free(command.cmd);
		free(input);
		if (status == -1)
			return (status);
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	// Cloner l'environnement
	loop(env);
}
