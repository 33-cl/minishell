/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:30:04 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/30 14:55:30 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// INFILE

// OUTFILE
static int	get_out(t_command *command)
{
	size_t	i;
	size_t	len_out;
	int		fd;
	char	type;

	i = 0;
	len_out = ft_tablen(command->redir.out);
	if (len_out == 0)
		return (0);
	type = command->redir.out[i][0];
	command->redir.out[i]++;
	if (type == '1')
		fd = open(command->redir.out[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(command->redir.out[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (1);
	while (i++, i < len_out)
	{
		type = command->redir.out[i][0];
		command->redir.out[i]++;
		close(fd);
		if (type == '1')
			fd = open(command->redir.out[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(command->redir.out[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
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
			write(2, "\n", 1);
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
	int	old_stdout;
	
	old_stdout = dup(STDOUT_FILENO);
    // get_in
	if (!get_out(command))
		command->status = execution(command, env);

	dup2(old_stdout, STDOUT_FILENO);
	return (command->status);
}
