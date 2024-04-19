/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:30:04 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/20 00:33:29 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Execute la commande prise en entree
	Renvoie un booleen qui indique si il y a une erreur
*/

int execute(t_command *command, char **env, int status)
{
    char	*path;
	pid_t	pid;
    
    if (!ft_strcmp(command->args[0], "echo"))
        echo(command);
    else if (!ft_strcmp(command->args[0], "cd"))
        status = cd(command);
	else if (!ft_strcmp(command->args[0], "pwd"))
		status = pwd();
    else
    {
        path = get_path(command->args[0], env);
        if (path)
        {
            pid = fork();
			if (pid == -1)
				return (-1);
			else if (pid == 0)
				execve(path, command->args, env);
			waitpid(pid, &status, 0);
			// Mettre a jour le status en fonction de la valeur recuperee avec waitpid
		}
		else
		{
			write(2, "minishell: command not found : ", 31);
			write(2, command->args[0], ft_strlen(command->args[0]));
			write(1, "\n", 1);
			status = 127;
		}
		free(path);
    }

    return (status);
}
