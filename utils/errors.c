/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:11:59 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/08 20:23:42 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Returns a bool based on is the command is considered as a dir
*/

int	is_a_dir(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '.' && cmd[i] != '/')
			return (0);
		if (cmd[i] == '.' && cmd[i + 1] && cmd[i + 1] == '.'
			&& cmd[i + 2] && cmd[i + 2] == '.')
			return (0);
		i++;
	}
	return (1);
}

/*
	Displays an error msg and returns the status erro
*/

int	print_error(int type_error, char *str)
{
	write(2, "minishell: ", 11);
	if (str)
		write(2, str, ft_strlen(str));
	if (type_error == FILE_NOT_FOUND)
		return (write(2, ": no such file or directory\n", 28), 127);
	else if (type_error == COMMAND_NOT_FOUND)
		return (write(2, ": command not found\n", 20), 127);
	else if (type_error == IS_A_DIRECTORY)
		return (write(2, ": Is a directory\n", 17), 126);
	else if (type_error == PERMISSION_DENIED)
		return (write(2, ": Permission denied\n", 20), 126);
	else if (type_error == ARGUMENT_REQUIRED)
		return (write(2, FAR, 62), 2);
	else if (type_error == TOO_MANY_ARGS)
		return (write(2, " : too many arguments\n", 22), 1);
	else if (type_error == NOT_VALID_ID)
		return (write(2, "': not a valid identifier\n", 26), 1);
	return (0);
}
