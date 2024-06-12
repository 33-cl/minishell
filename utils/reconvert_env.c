/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconvert_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:44:24 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/10 18:54:49 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int    ft_lstsize(t_env *lst)
{
    size_t    count;

    count = 0;
    while (lst != NULL)
    {
        lst = lst->next;
        count++;
    }
    return (count);
}

static void    set_prev_pointers(t_env *env)
{
    t_env    *current;
    t_env    *prev;

    current = env;
    prev = NULL;
    while (current != NULL)
    {
        current->prev = prev;
        prev = current;
        current = current->next;
    }
}

char    **t_env_to_array(t_env *env)
{
    int        size;
    char    **final_array;
    t_env    *current;
    int        i;
    char    *temp;

    set_prev_pointers(env);
    size = ft_lstsize(env);
    final_array = malloc(sizeof(char *) * (size + 1));
    if (!final_array)
        return (NULL);
    current = env;
    while (current->next != NULL)
        current = current->next;
    i = 0;
    while (current != NULL)
    {
        temp = ft_strjoin(current->name, "=");
        final_array[i] = ft_strjoin(temp, current->value);
        free(temp);
        current = current->prev;
        i++;
    }
    final_array[i] = NULL;
    return (final_array);
}
