/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:50:50 by odx               #+#    #+#             */
/*   Updated: 2024/07/07 12:01:51 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_final_node(t_cmd *node)
{
	if (node == NULL)
	{
		printf("Node is NULL\n");
		return ;
	}
	print_command(node->cmd);
	print_arguments(node->args);
	print_heredoc_delimiters(node->heredoc_delimiters);
	printf("Number of Heredocs: %d\n", node->nb_heredocs);
	print_redirections(node->redir);
	printf("-------------------\n");
}

void	print_final_list(t_cmd *list)
{
	t_cmd	*current;
	int		node_index;

	current = list;
	node_index = 0;
	while (current != NULL)
	{
		printf("Node %d:\n", node_index);
		print_final_node(current);
		current = current->next;
		node_index++;
	}
}

void	print_args(t_args *args)
{
	if (args == NULL)
	{
		printf("None\n");
		return ;
	}
	printf("[ ");
	while (args != NULL)
	{
		printf("{ Value: \"%s\", Type: %d, Quotes: %d", args->value, \
		args->type, args->quotes);
		if (args->multi_quoted_args != NULL)
		{
			printf(", Multi-Quoted Args: ");
			print_args(args->multi_quoted_args);
		}
		printf(" }");
		args = args->next;
		if (args != NULL)
			printf(", ");
	}
	printf(" ]\n");
}

void	print_command_details(t_command *command)
{
	t_command	*current;
	int			count;

	current = command;
	count = 0;
	while (current != NULL)
	{
		printf("Command %d:\n", ++count);
		if (current->cmd != NULL)
			printf("  cmd: \"%s\"\n", current->cmd);
		else
			printf("  cmd: \"None\"\n");
		printf("  args: ");
		print_args(current->args);
		printf("  Redirections:\n    in: ");
		print_string_array(current->redir);
		printf("\n");
		printf("  heredoc_delimiters: ");
		print_string_array(current->heredoc_delimiters);
		printf("\n");
		printf("  nb_heredocs: %d\n", current->nb_heredocs);
		current = current->next;
		if (current != NULL)
			printf("\n");
	}
}

void	test_heredoc_pipe(t_cmd *cmd)
{
	t_cmd	*current;
	char	buffer[1024];
	ssize_t	bytes_read;

	current = cmd;
	while (current != NULL)
	{
		if (current->fd_heredoc[0] != -1)
		{
			bytes_read = read(current->fd_heredoc[0], buffer, \
			sizeof(buffer) - 1);
			if (bytes_read >= 0)
			{
				buffer[bytes_read] = '\0';
				printf("Contenu du pipe pour le nœud: %s\n", buffer);
			}
			else
				perror("read");
			close(current->fd_heredoc[0]);
		}
		current = current->next;
	}
}
