/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:37:28 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/30 18:12:23 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Agis exactement comme la commande cd

	Renvoie 1 et un message d'erreur en cas d'erreur de chdir
*/

int cd(t_command *command)
{
	int	status;
	
	status = 0;
	// Cas "classique"
	if (ft_tablen(command->args) >= 3)
	{
		write(2, "minishell: cd : too many arguments\n", 35);
		return (1);
	}
	if (command->args[1])
	{
		status = chdir(command->args[1]);
		if (status == -1)
		{
			print_error(FILE_NOT_FOUND, command->args[1]);
			return (1);
		}
	}
	else
		(void)command;// Prendre en compte le cas de cd sans arg
	return (0);
}
