/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:51:09 by odx               #+#    #+#             */
/*   Updated: 2024/07/07 12:00:46 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_string_array(char **array)
{
	int	i;

	if (array == NULL)
	{
		printf("(null)");
		return ;
	}
	i = 0;
	while (array[i] != NULL)
	{
		printf("%s", array[i]);
		if (array[i + 1] != NULL)
			printf("; ");
		i++;
	}
}

void	print_command(char *cmd)
{
	if (cmd != NULL)
		printf("Command: %s\n", cmd);
	else
		printf("Command: (null)\n");
}

void	print_arguments(char **args)
{
	printf("Arguments: ");
	if (args != NULL)
		print_string_array(args);
	else
		printf("(null)");
	printf("\n");
}

void	print_heredoc_delimiters(char **heredoc_delimiters)
{
	printf("Heredoc Delimiters: ");
	if (heredoc_delimiters != NULL)
		print_string_array(heredoc_delimiters);
	else
		printf("(null)");
	printf("\n");
}

void	print_redirections(char **redir)
{
	printf("Redirections: ");
	if (redir != NULL)
		print_string_array(redir);
	else
		printf("(null)");
	printf("\n");
}
