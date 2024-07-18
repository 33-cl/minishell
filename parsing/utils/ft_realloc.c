/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 23:32:39 by odx               #+#    #+#             */
/*   Updated: 2024/07/17 22:46:35 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	realloc_args_array(t_args *current, t_cmd *current_final)
{
	int		len;

	len = ft_lstsize_final(current);
	current_final->args = ft_realloc_string_array_final (current_final->args, \
	len + 1);
	if (current_final->args == NULL)
	{
		return (2);
	}
	return (0);
}

void	*ft_realloc_old_size(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		free(ptr);
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
	new_array = ft_realloc_old_size(array, old_size * sizeof(char *), \
	(i + new_size + 1) * sizeof(char *));
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
