/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:41:01 by qordoux           #+#    #+#             */
/*   Updated: 2024/05/21 16:40:10 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// bool	add_redirection(char ***redirections, char *filename, int choice)
// {
// 	int		count;
// 	char	**new_string;
// 	char	*check_string;

// 	count = 0;
// 	if (*redirections != NULL)
// 	{
// 		while ((*redirections)[count] != NULL)
// 			count++;
// 	}
// 	new_string = ft_realloc(*redirections, sizeof(char *) * count + 2);
// 	if (new_string == NULL)
// 		return (false);
// 	check_string = ft_strdup(filename);
// 	if (choice == 1)
// 		check_string = add_one_char_before(check_string, '1');	
// 	else if (choice == 2)
// 		check_string = add_one_char_before(check_string, '2');
// 	else
// 		check_string = ft_strdup(filename);
// 	new_string[count] = check_string;
// 	if (new_string[count] == NULL)
// 	{
// 		// free(new_string);
// 		return (false);
// 	}
// 	new_string[count + 1] = NULL;
// 	*redirections = new_string;
// 	return (true);
// }

// bool	determine_redirection_type(t_command *command, char *token, char *next_token)
// {
// 	// gerer si add redirection echoue
// 	if (ft_strcmp(token, "<") == 0)
// 		{
// 			add_redirection(&command->redir, next_token, 1);
// 			return (true);
// 		}
// 		else if (ft_strcmp(token, "<<") == 0)
// 		{
// 			add_redirection(&command->redir, next_token, 2);
// 			add_redirection(&command->heredoc_delimiters, next_token, 3);//segfault ici
// 			return (true);
// 		}
// 		else if (ft_strcmp(token, ">") == 0)
// 		{
// 			add_redirection(&command->redir, next_token, 1);
// 			return (true);
// 		}
// 		else if (ft_strcmp(token, ">>") == 0)
// 		{
// 			add_redirection(&command->redir, next_token, 2);
// 			return (true);
// 		}
// 	return (false);
// }


// bool	take_fill_redirection(t_command *command, char *token)
// {
// 	char	*next_token;

// 	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0 || \
// 	ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0)
// 	{
// 		next_token = ft_strtok_space(NULL, " ");
// 		if (next_token == NULL)
// 			return (true);//signaler l'erreur la je retourne true
// 		if (!determine_redirection_type(command, token, next_token))
// 			return (false);
// 	// que se passe il si add_redirection met un NULL dans redir.in ou outfile?
// 	// AJOUTER LA GESTION DE SI ADD REDIRECTION RENVOIE FALSE
// 	}
// 	return (false);
// }
