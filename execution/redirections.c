/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:56:15 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/12 14:45:01 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Reinitialise l'entree et la sortie standard
*/

int	reset_std(int old_stdin, int old_stdout)
{
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);

	return (0);
}

/*
	Ouvre le fichier de redirection en fonction du type de redirection

	return un int correspondant au fd
	-1 en cas d'erreur
*/

int	open_type(char *file_name, char type, int *fd)
{
	// Ouverture du fichier en fonction de la redirection effectuee
	if (type == '<')
		*fd = open(file_name, O_RDONLY, 0777);
	else if (type == '>')
		*fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		*fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);

	// Check du open
	if (*fd == -1 && errno == EACCES)
		return (print_error(PERMISSION_DENIED, file_name), -1);
	else if (*fd == -1)
		return (print_error(FILE_NOT_FOUND, file_name), -1);


	return (*fd);
}

/*
	Met a jour l'entree de la commande
*/

int	get_in(t_cmd *command)
{
	size_t	i;
	size_t	len_in;
	char	type;
	int		fd;

	i = -1;
	fd = -1;
	len_in = ft_tablen(command->redir);
	if (len_in == 0)
		return (0);
	while (i++, i < len_in)
	{
		type = command->redir[i][0];
		command->redir[i]++;
		if (type == '<' && open_type(command->redir[i], type, &fd) == -1)
			return (-1);
		else if (type == '-')
			dup2(command->fd_heredoc, STDIN_FILENO);
	}
	if (fd != -1)
		return (dup2(fd, STDOUT_FILENO), close(fd), 0);
	return (0);
}

/*
	Met a jour la sortie de la commande
*/

int	get_out(t_cmd *command)
{
	size_t	i;
	size_t	len_out;
	char	type;
	int		fd;

	i = -1;
	fd = -1;
	len_out = ft_tablen(command->redir);
	if (len_out == 0)
		return (0);
	while (i++, i < len_out)
	{
		type = command->redir[i][0];
		command->redir[i]++;
		if (type == '>' || type == '+')
		{
			if (open_type(command->redir[i], type, &fd) == -1)
				return (-1);				
			command->redir_out = true;
		}
		command->redir[i]--;
	}
	if (fd != -1)
		return (dup2(fd, STDOUT_FILENO), close(fd), 0);
	return (0);
}
