/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:26:30 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/21 16:54:33 by maeferre         ###   ########.fr       */
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
	t_command   command;
	char        *input;

	command.status = 0;
	while (1)
	{
		input = prompt(command.status);
		if (!input)
			return (1);
		parsing(&command, input);
		command.status = execute(&command, env);
		ft_free_tab(command.args);
		free(command.cmd);
		free(input);
		if (command.status == -1)
			return (command.status);
	}
	return (command.status);
}

int main(int argc, char **argv, char **env)
{
	int	status;
	
	(void)argc;
	(void)argv;
	status = 0;
	// Cloner l'environnement
	status = loop(env);

	return (status);
}
