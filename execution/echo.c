/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:21:51 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/30 17:24:47 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
    Reproduction de la commande echo
    "echo -n" retire le '\n' a la fin du print
*/

void    echo(t_command *command)
{
    // Modifier pour le parsing de command->cmd


    if (ft_strlen(*command->args) >= 2 && !ft_strcmp(command->args[1], "-n"))
        printf("%s", command->cmd + 8);
    else
        printf("%s\n", command->cmd + 5);
}