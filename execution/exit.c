/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:35:29 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/22 05:34:23 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Checks if exit command is called and handles errors
*/

bool	check_exit(t_cmd *command, int *status)
{
	int	len;

	if (!command->args)
		return (false);
	len = ft_tablen(command->args);
	if (len == 0 || ft_strcmp(command->args[0], "exit"))
		return (false);
	if (len == 1)
		return (write(1, "exit\n", 5), true);
	write(1, "exit\n", 5);
	if (!ft_isnumber(command->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(command->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		*status = 2;
	}
	else
	{
		*status = ft_atoi(command->args[1]);
		if (len > 2)
			return (*status = 1,
				write(2, "minishell : exit: too many arguments\n", 25), false);
	}
	return (true);
}
