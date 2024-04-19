/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:37:28 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/19 22:54:55 by maeferre         ###   ########.fr       */
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
	if (command->args[1])
	{
		status = chdir(command->args[1]);
		if (status == -1)
		{
			write(2, "cd : no such file or directory: ", 32);
			write(2, command->args[1], ft_strlen(command->args[1]));
			write(2, "\n", 1);
			return (1);
		}
	}
	else
		;// Prendre en compte le cas de cd sans arg
	return (0);
}