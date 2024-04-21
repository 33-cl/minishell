/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:30:04 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/21 17:12:20 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// INFILE

// OUTFILE
static void	get_out(t_command *command)
{
	size_t	i;
	size_t	len_out;
	int		fd;

	i = 0;
	len_out = ft_tablen(command->redir.out);
	if (len_out == 0);
		return;
	command->redir.out++;
	fd = open(command->redir.out, O_RDWR | O_CREAT | O_TRUNC, 0000644);
	if 
}	

// EXECUTION
static int	execution(t_command *command, char **env)
{
	char	*path;
	pid_t	pid;
    
    if (!command->args[0])
		return (command->status);
	if (!ft_strcmp(command->args[0], "echo"))
        echo(command);
    else if (!ft_strcmp(command->args[0], "cd"))
        command->status = cd(command);
	else if (!ft_strcmp(command->args[0], "pwd"))
		command->status = pwd();
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
			waitpid(pid, &command->status, 0);
			// Mettre a jour le status en fonction de la valeur recuperee avec waitpid
		}
		else
		{
			write(2, "minishell: command not found : ", 31);
			write(2, command->args[0], ft_strlen(command->args[0]));
			write(1, "\n", 1);
			command->status = 127;
		}
		free(path);
    }
	return (command->status);
}

/*
	Execute la commande prise en entree
	Renvoie un booleen qui indique si il y a une erreur
*/

int	execute(t_command *command, char **env)
{
    // get_in
	// get_out
	command->status = execution(command, env);

	return (command->status);
}
