/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:15:14 by qordoux           #+#    #+#             */
/*   Updated: 2024/07/19 00:38:21 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parsing(char *input, t_env *env, int *status, int *old_status)
{
	t_command	*command;
	t_cmd		*final_cmd;

	command = NULL;
	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
	{
		*status = 1;
		return (NULL);
	}
	signal(SIGINT, sigint_handler_heredoc);
	init_command_fields(command);
	if (input[0] != '\0')
		*status = create_struct(command, input, env, status);
	final_cmd = command->final_cmd;
	free_command(&command);
	if (*status != 0 && *status != 130)
	{
		*old_status = *status;
		if (input)
			free(input);
		input = NULL;
		free_final_list(&final_cmd);
	}
	return (final_cmd);
}
