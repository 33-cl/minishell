/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconvert_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:44:24 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/17 23:06:45 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_lstsize(t_env *lst)
{
	size_t	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

static void	set_prev_pointers(t_env *env)
{
	t_env	*current;
	t_env	*prev;

	current = env;
	prev = NULL;
	while (current != NULL)
	{
		current->prev = prev;
		prev = current;
		current = current->next;
	}
}

static int	convert_env_to_array(t_env *env, char **final_array)
{
	int			i;
	t_env		*current;
	char		*temp;

	i = 0;
	current = env;
	while (current->next != NULL)
		current = current->next;
	while (current != NULL)
	{
		temp = ft_strjoin(current->name, "=");
		if (!temp)
			return (0);
		final_array[i] = ft_strjoin(temp, current->value);
		if (!final_array[i])
		{
			free(temp);
			return (0);
		}
		free(temp);
		current = current->prev;
		i++;
	}
	final_array[i] = NULL;
	return (1);
}

char	**t_env_to_array(t_env *env)
{
	int			size;
	char		**final_array;

	size = ft_lstsize(env);
	final_array = malloc(sizeof(char *) * (size + 1));
	if (!final_array)
		return (NULL);
	set_prev_pointers(env);
	if (!convert_env_to_array(env, final_array))
	{
		ft_free_tab(final_array);
		return (NULL);
	}
	return (free_env(&env), final_array);
}
