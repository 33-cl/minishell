/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:56:15 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/22 05:32:58 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Reinitializes in
*/

bool	reset_stdin(t_cmd *cmd, t_process *infos)
{
	cmd->redir_out = 0;
	if (dup2(infos->stdin, STDOUT_FILENO) == -1)
		return (false);
	close(infos->stdout);
	return (true);
}

/*
	Reinitializes in and out
*/

bool	reset_std(t_process *infos)
{
	if (dup2(infos->stdin, STDIN_FILENO) == -1)
		return (false);
	close(infos->stdin);
	if (dup2(infos->stdout, STDOUT_FILENO) == -1)
		return (false);
	close(infos->stdout);
	return (true);
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

int	get_in(t_cmd *command, size_t i, int fd)
{
	size_t	len_in;
	char	type;

	len_in = ft_tablen(command->redir);
	if (len_in == 0)
		return (0);
	while (i++, i < len_in)
	{
		if (fd != -1)
			close(fd);
		type = command->redir[i][0];
		command->redir[i]++;
		if (type == '<' || type == '-')
			if (open_type(command, command->redir[i], type, &fd) == -1)
				return (command->redir[i]--, -1);
		command->redir[i]--;
	}
	if (fd != -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (-1);
		close(fd);
	}
	return (0);
}

/*
	Updates the out
*/

int	get_out(t_cmd *command, size_t i, int fd)
{
	size_t	len_out;
	char	type;

	len_out = ft_tablen(command->redir);
	while (i++, i < len_out)
	{
		if (fd != -1)
			close(fd);
		type = command->redir[i][0];
		command->redir[i]++;
		if (type == '>' || type == '+')
		{
			if (open_type(command, command->redir[i], type, &fd) == -1)
				return (command->redir[i]--, -1);
			command->redir_out = true;
		}
		command->redir[i]--;
	}
	if (fd != -1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (-1);
		close(fd);
	}
	return (0);
}
