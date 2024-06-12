/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:37:28 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/10 17:22:39 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Agis exactement comme la commande cd

	Renvoie un status ou -1 en cas d'erreur de malloc()
*/

int cd(t_cmd *command, t_env *env)
{
	if (ft_tablen(command->args) >= 3)
		return (print_error(TOO_MANY_ARGS, "cd"));
	if (command->args[1])
	{
		if (command->args[1][0] == '-' && !command->args[1][1])
			if (chdir(get_env(&env, "OLDPWD")) == -1)
				return (print_error(FILE_NOT_FOUND, get_env(&env, "OLDPWD")), 1);
		if (chdir(command->args[1]) == -1)
			return (print_error(FILE_NOT_FOUND, command->args[1]), 1);
	}
	else
		if (chdir(get_env(&env, "HOME")) == -1)
			return (print_error(FILE_NOT_FOUND, get_env(&env, "HOME")), 1);
	if (!set_env(&env, "OLD_PWD", get_env(&env, "PWD")))
		return (-1);
	if (!set_env(&env, "PWD", getcwd(NULL, 0)))
		return (-1);
	return (0);
}
