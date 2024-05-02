/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:26:30 by maeferre          #+#    #+#             */
/*   Updated: 2024/05/02 16:24:45 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_command *command, char *input)
{
	command->args = ft_split(input, ' ');
	command->cmd = ft_strdup(input);
	command->redir.out = malloc(sizeof(char *) * 3);
	command->redir.out[0] = NULL;//ft_strdup("1outfile");
	command->redir.out[1] = NULL;
	command->redir.out[2] = NULL;
	command->redir.in = malloc(sizeof(char *) * 3);
	command->redir.in[0] = ft_strdup("1Makefile");
	command->redir.in[1] = NULL;
	command->redir.in[2] = NULL;
	command->next = NULL;
	command->next = malloc(sizeof(t_command));
	command->next->next = NULL;
	command->next->args = ft_split("grep .a", ' ');
	command->next->cmd = ft_strdup("grep .a");
	// command->next->next = malloc(sizeof(t_command));
	// command->next->next->next = NULL;
	// command->next->next->args = ft_split("grep .a", ' ');
	// command->next->next->cmd = ft_strdup("grep .a");
	// command->next->next = malloc(sizeof(t_command));
	// command->next->next->next->next = NULL;
	// command->next->next->next->args = ft_split("grep g", ' ');
	// command->next->next->next->cmd = ft_strdup("grep g");
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
