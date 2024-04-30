/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:26:30 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/30 14:57:44 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_command *command, char *input)
{
	command->args = ft_split(input, ' ');
	command->cmd = ft_strdup(input);
	command->redir.out = malloc(sizeof(char *) * 3);
	command->redir.out[0] = ft_strdup("2outfile");
	command->redir.out[1] = NULL;
	command->redir.out[2] = NULL;
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
		ft_free_tab(command.redir.out);
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
