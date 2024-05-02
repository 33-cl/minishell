/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:30:04 by maeferre          #+#    #+#             */
/*   Updated: 2024/05/02 16:29:55 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Met a jour l'entree de la commande
*/

static int	get_in(t_command *command)
{
	size_t	i;
	size_t	len_in;
	int		fd;
	char	type;

	fd = 0; // A supprimer quand j'aurais implemente les heredoc
	i = 0;
	len_in = ft_tablen(command->redir.in);
	if (len_in == 0)
		return (0);
	type = command->redir.in[i][0];
	command->redir.in[i]++;
	if (type == '1')
		fd = open(command->redir.in[i], O_RDONLY, 0777);
	if (fd == -1)
		return (print_error(FILE_NOT_FOUND, command->redir.in[i]), 1);
	while (i++, i < len_in)
	{
		type = command->redir.in[i][0];
		command->redir.in++;
		close(fd);
		if (type == '1')
			fd = open(command->redir.in[i], O_RDONLY, 0777);
		if (fd == -1)
			return (print_error(FILE_NOT_FOUND, command->redir.in[i]), 1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/*
	Met a jour la sortie de la commande
*/

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


/*
	Execute la commande lorsqu'on connait l'entree et la sortie de la commande
*/

static int	execution(t_command *command, char **env)
{
	char	*path;
	
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
			execve(path, command->args, env);
			// Mettre a jour le status en fonction de la valeur recuperee avec waitpid
		else
		{
			print_error(COMMAND_NOT_FOUND, command->args[0]);
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

int execute(t_command *command, char **env)
{
	pid_t	pid;
	int		status;
	int		old_stdin;
	int		old_stdout;
	int		pipefd[2];

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	status = 0;

	while (command != NULL)
	{
		if (!get_in(command) && !get_out(command))
		{
			if (command->next != NULL)
				if (pipe(pipefd) == -1)
					return (-1);
			pid = fork();
			if (pid == -1)
				return (-1);
			else if (pid == 0)
			{
				if (command->next != NULL)
				{
					close(pipefd[0]);
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[1]);
				}
				command->status = execution(command, env);
				return (command->status);
			}
			else
			{
				if (command->next != NULL)
				{
					close(pipefd[1]);
					dup2(pipefd[0], STDIN_FILENO);
					close(pipefd[0]);
				}
				waitpid(pid, &status, 0);
			}
		}
		command = command->next;
	}
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);
	return (status);
}
