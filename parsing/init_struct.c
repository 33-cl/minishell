/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:13:57 by qordoux           #+#    #+#             */
/*   Updated: 2024/07/17 22:07:43 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_struct(t_command *command, char *input, t_env *env, int *status)
{
	int	result;

	result = initialize_struct(command, input);
	if (result != 0)
		return (result);
	return (finalize_struct(command, env, status));
}

int	initialize_struct(t_command *command, char *input)
{
	char	*input_copy;

	input_copy = ft_strdup(input);
	if (!input_copy)
		return (1);
	input_copy = put_space_before_redir(input_copy, -1);
	if (!input_copy)
		return (1);
	if (!parse_and_fill_struct(command, input_copy))
		return (free(input_copy), 1);
	free(input_copy);
	if (!syntax_error(command))
		return (2);
	if (!add_heredoc_delimiter(command, command->args))
		return (1);
	remove_quotes_in_delimiter(command);
	return (0);
}

int	finalize_struct(t_command *command, t_env *env, int *status)
{
	int	error;

	error = 0;
	heredoc_init(command, &error);
	if (error == 1)
		return (1);
	command = replace_expand(command, env, status, &error);
	if (error == 1 || *status == -1)
		return (1);
	if (!syntax_error_after(command))
		return (2);
	if (!put_everything_in_final_list(command))
		return (1);
	add_heredoc_to_fd(command->final_cmd);
	return (0);
}
