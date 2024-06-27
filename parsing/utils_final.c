/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_final.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:08:22 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/26 16:57:52 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// a ameliorer, pas besoin de j je crois

void	*ft_realloc_old_size_bis(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t copy_size;

    if (new_size == 0)
	{
        free(ptr);
        return (NULL);
    }
	new_ptr = malloc(new_size);
    if (new_ptr == NULL)
	{
		free(ptr);//j' ai ajoute ca
        return (NULL);
	}
    if (ptr != NULL)
	{
        if (old_size < new_size)
            copy_size = old_size;
        else
            copy_size = new_size;
        ft_memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }
    return (new_ptr);
}
char	**ft_realloc_string_array_final_bis(char **array, size_t new_size)
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
	new_array = ft_realloc_old_size_bis(array, old_size * sizeof(char *), (i + new_size + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	j = i;
	while (j < i + new_size + 1)
	{
		new_array[j] = NULL;
		j++;
	}
	return (new_array);
}

char	**ft_realloc_string_array_final(char **array, size_t new_size)
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
		return (NULL);
	j = i;
	while (j < i + new_size + 1)
	{
		new_array[j] = NULL;
		j++;
	}
	return (new_array);
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
		return (false);
	memset(*list, 0, sizeof(t_cmd));//CHANGER MEMSET
    args_size = ft_lstsize_final(command->args) + 1;
	(*list)->args = malloc((args_size + 1) * sizeof(char *));// ici ca merde ptet patcher le 2*, avec un realloc quand necessaire
	if (!(*list)->args)
	{
		free(*list);
		return (false);
	}
	(*list)->malloc_failed = false;
	(*list)->args[0] = NULL;
	(*list)->heredoc_delimiters = NULL;
	(*list)->nb_heredocs = 0;
	// (*list)->fd_heredoc = 0;
	(*list)->redir = NULL;
	(*list)->next = NULL;
	return (true);
}

bool	init_new_final_list_node(t_cmd **head, t_cmd **current, t_command *command)
{
    t_cmd	*new_node;

    if (!init_final_list(&new_node, command))
		return (false);
    if (*head == NULL)
        *head = new_node;
    else
        (*current)->next = new_node;
    *current = new_node;
	return (true);
}
