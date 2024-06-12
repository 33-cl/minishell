/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_final.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:08:22 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/12 15:12:28 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// a ameliorer, pas besoin de j je crois
char **ft_realloc_string_array_final(char **array, size_t new_size)
{
    size_t		i;
    size_t		old_size;
    char		**new_array;
    size_t		j;

    i = 0;
    old_size = 0;
    while (array && array[i])
    {
        i++;
        old_size++;
    }
    new_array = ft_realloc_old_size(array, old_size * sizeof(char *), (i + new_size + 1) * sizeof(char *));
    if (!new_array)
        return NULL;
    j = i;
    while (j < i + new_size + 1)
    {
        new_array[j] = NULL;
        j++;
    }
    
    return new_array;
}
int ft_lstsize_final(t_args *lst)
{
	size_t	count;

	count = 0;
	while (lst != NULL)
	{
        if (lst->type == 2 && lst->quotes == 0)
            return (count);// est-ce que je count pas une fois de trop?
		lst = lst->next;
		count++;
	}
	return (count);
}


bool	init_final_list(t_cmd **list, t_command *command)
{
    int    args_size;

	(*list) = malloc(sizeof(t_cmd));
	if (!(*list))
		return false;
	ft_memset(*list, 0, sizeof(t_cmd));
    args_size = ft_lstsize_final(command->args);
	(*list)->args = malloc((args_size + 1) * sizeof(char *));// ici ca merde ptet patcher le 2*, avec un realloc quand necessaire
	if (!(*list)->args)
		return false;
	(*list)->args[0] = NULL;
	(*list)->heredoc_delimiters = NULL;
	(*list)->nb_heredocs = 0;
	(*list)->fd_heredoc = 0;
	(*list)->redir = NULL;
	(*list)->next = NULL;
	return (true);
}

void	init_new_final_list_node(t_cmd **head, t_cmd **current, t_command *command)
{
    t_cmd	*new_node;

    init_final_list(&new_node, command);
    if (*head == NULL)
        *head = new_node;
    else
        (*current)->next = new_node;
    *current = new_node;
}
