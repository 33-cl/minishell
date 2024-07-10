/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:56:15 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/03 17:09:12 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Reinitilizes in and out
*/

void	reset_std(t_process *infos)
{
	dup2(infos->stdin, STDIN_FILENO);
	close(infos->stdin);
	dup2(infos->stdout, STDOUT_FILENO);
	close(infos->stdout);
}

/*
	Opens the right file descriptor based on the redirection type
	Returns an int for the fd
	-1 in case of open() error
*/

int	open_type(t_cmd *command, char *file_name, char type, int *fd)
{
	if (type == '<')
		*fd = open(file_name, O_RDONLY, 0777);
	else if (type == '>')
		*fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == '+')
		*fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*fd = command->fd_heredoc[0];
	if (*fd == -1 && errno == EACCES)
		return (print_error(PERMISSION_DENIED, file_name), -1);
	else if (*fd == -1)
		return (print_error(FILE_NOT_FOUND, file_name), -1);
	return (*fd);
}

/*
	Updates the in
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
		if (type == '<' || type == '-')
			if (open_type(command, command->redir[i], type, &fd) == -1)
				return (-1);
		command->redir[i]--;
	}
	if (fd != -1)
		return (dup2(fd, STDIN_FILENO), close(fd), 0);
	return (0);
}

/*
	Updates the out
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
			if (open_type(command, command->redir[i], type, &fd) == -1)
				return (-1);
			command->redir_out = true;
		}
		command->redir[i]--;
	}
	if (fd != -1)
		return (dup2(fd, STDOUT_FILENO), close(fd), 0);
	return (0);
}
