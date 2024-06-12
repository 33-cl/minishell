/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:45:06 by maeferre          #+#    #+#             */
/*   Updated: 2024/05/08 13:34:46 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Simulation d'un heredoc qui prend en parametres son delimiter
	et le fd dans lequel il doit ecrire
	
	>minishell$ <<delimiter cat
	> Hello world
	> blabla
	> delimiter
	Hello world
	blabla
*/

// static int	heredoc(char *delimiter);

// int heredoc_init(t_command *command)
// {
// 	t_command	*first_command;
// 	int			i;
// 	int			do_it;

// 	first_command = command;
// 	command->fd_heredoc = -2;
// 	do_it = command->nb_heredocs > 0;
// 	while (command->next != NULL || do_it == 1)
// 	{
// 		do_it--;
// 		i = 0;
// 		while (i < command->nb_heredocs)
// 		{
// 			if (command->fd_heredoc != -2)
// 				close(command->fd_heredoc);
// 			command->fd_heredoc = heredoc(command->heredoc_delimiters[i]);
// 			if (command->fd_heredoc == -1)
// 				return (1);
// 			i++;
// 		}
// 		if (command->next != NULL)
// 			command = command->next;
// 	}
// 	command = first_command;
// 	return (0);
// }

// static int	heredoc(char *delimiter)
// {
// 	char	*input;
// 	int		fd;

// 	fd = open("/tmp/.heredoc", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
// 	if (fd == -1)
// 		return (-1);
// 	input = readline(">");
// 	// if (ft_strcmp(input, delimiter))
// 	// {
// 	// 	write(fd, input, ft_strlen(input));
// 	// 	write(fd, "\n", 1);
// 	// 	free(input);
// 	// 	input = readline(">");
// 	// }
// 	while (ft_strcmp(input, delimiter))
// 	{
// 		write(fd, input, ft_strlen(input));
// 		write(fd, "\n", 1);
// 		free(input);
// 		input = readline(">");
// 	}
// 	free(input);
// 	close(fd);
// 	fd = open("/tmp/.heredoc", O_RDONLY);
// 	return (fd);
// }
