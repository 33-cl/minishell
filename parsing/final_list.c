/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:30:32 by qordoux           #+#    #+#             */
/*   Updated: 2024/05/29 19:59:17 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// pour la commande, comme je peux avoir des arguments apres la redirection il lui faut tout ce qu'il y a avant le pipe? 

bool	put_everything_in_final_list(t_command *command)
{
	t_args				*current;
	t_cmd				*head_final_list;
	t_cmd				*current_final;
	int					i;
	int					j;
	
	head_final_list = NULL;
	current_final = NULL;
	current = command->args;
	i = 0;
	j = 0;
	init_new_final_list_node(&head_final_list, &current_final, command);
	while (current != NULL)
	{
		if (current->type == 2 && current->quotes == 0)
		{
			init_new_final_list_node(&head_final_list, &current_final, command);
			i = 0;
			j = 0;
			current = current->next;
			continue;
		}
		if (handle_delimiter_final(&current, &current_final, &j))
			continue;
		process_quoted_or_unquoted(current, current_final, &i);
		current = current->next;
	}
	if (current_final != NULL && current_final->args != NULL)
		current_final->args[i] = NULL;
	// print_final_list(head_final_list);
	command->final_cmd = head_final_list;
	return (true);
}

// bool	add_heredoc_to_tempfile(t_cmd *final_list)
// {
// 	t_cmd	*current;
// 	int				i;
// 	char			*heredoc_content;
// 	int				temp_fd;

// 	current = final_list;
// 	while (current != NULL)
// 	{
// 		i = 0;
// 		while(current->redir[i])
// 		{
// 			if (current->redir[i][0] == '-')
// 			{
// 				heredoc_content = ft_strdup(current->redir[i]+ 1);
// 				temp_fd = open(".heredoc_temp",O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 				if (temp_fd < 0)
// 				{
// 					perror("open");
// 					return false;
// 				}
// 				ft_putstr_fd(heredoc_content, temp_fd);
// 				current->fd_heredoc = temp_fd;
// 				free(heredoc_content);
// 			}
// 			i++;
// 		}
// 		print_file_content(".heredoc_temp");
// 		current = current->next;
// 	}
// 	close(temp_fd);
// 	return (true);
// }

// void	print_file_content(const char *filename)
// {
//     int fd = open(filename, O_RDONLY);
//     if (fd < 0)
// 	{
//         perror("open");
//         return;
//     }

//     char buffer[1024];
//     ssize_t bytes_read;

//     while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
// 	{
//         buffer[bytes_read] = '\0'; // Assurer que la chaîne est bien terminée
//         printf("\nHEREDOC = %s\n", buffer);
//     }

//     if (bytes_read < 0)
//         perror("read");
//     close(fd);
// }

// quand j'ai un heredoc j'ai un /n avant la premere chaine du heredoc, pas sur que ce soit ce que je veux, par contre enctre chaque ligne du heredoc il ya un \n
//faire un garbage colletor (malloc qui balade une structure et qui ajoute a la structure le pointeur de chaque nouveau malloc du coup simple a free)
// dans l'exemple genre $9HOME il faut renvoyer home mais si c'est $HO9ME on ne renvoyer rien, corriger cela


// bool	put_everything_in_final_list(t_command *command)
// {
// 	t_args			*current;
// 	t_args			*current_multi_quoted_args;
// 	t_cmd	*head_final_list;
// 	t_cmd	*new_node;
// 	t_cmd	*current_final;
// 	int				i;
// 	int				j;
// 	char			*unquoted_result;

// 	j = 0;
// 	i = 0;
// 	new_node = NULL;
// 	head_final_list = NULL;
// 	current_final = NULL;
// 	// temp = ft_strdup("");

// 	current = command->args;
// 	while (current != NULL)
// 	{
// 		if (current->type == 2 && current->quotes == 0)
// 		{
// 			init_final_list(&new_node);
// 			if (current_final)
// 				current_final->next = new_node;
// 			else
// 				head_final_list = new_node;
// 			current_final = new_node;
// 			i = 0;
// 			current = current->next;
// 			j = 0;
// 			continue;
// 		}
// 		else 
// 		{
//             if (!head_final_list)
// 			{
//                 init_final_list(&head_final_list);
//                 current_final = head_final_list;
//             }
// 		}
// 		if (current->quotes == 0 && (ft_strcmp(current->value, "<<") == 0 || ft_strcmp(current->value, ">>") == 0 
// 		 || ft_strcmp(current->value, "<") == 0 || ft_strcmp(current->value, ">") == 0))
// 		{
// 			add_specifier_to_struct(&current_final, current, &j);
// 			current = current->next;
// 			if (current != NULL)
// 				current = current->next;
// 			continue;
// 		}
// 		current_multi_quoted_args = current->multi_quoted_args;
// 		if (current_multi_quoted_args)
// 			handle_multi_quoted_args(current_multi_quoted_args, current, current_final, &i);
// 		else
// 		{
// 			current_final->args = ft_realloc_string_array_final(current_final->args, 1);
// 			if (current->quotes != 0 && ft_strcmp(current->prev->value, "<<") != 0)
// 			{	
// 				unquoted_result = ft_unquote_result(current->value, current);
// 				current_final->args[i] = ft_strdup(unquoted_result);
// 			}
// 			else
// 				current_final->args[i] = ft_strdup(current->value);
// 			i++;
// 		}
// 		current = current->next;
// 	}
// 	current_final->args[i] = NULL;
// 	print_final_list(head_final_list);
// 	return(true);
// }