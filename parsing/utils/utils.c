/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 23:40:39 by odx               #+#    #+#             */
/*   Updated: 2024/07/07 00:20:02 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_final(t_args *lst)
{
	size_t	count;

	count = 0;
	while (lst != NULL)
	{
		if (lst->type == 2 && lst->quotes == 0)
			return (count);
		lst = lst->next;
		count++;
	}
	return (count);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	void	*ptr;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

int	duplicate_cmd(t_args *current, t_cmd *current_final)
{
	if (current_final->cmd)
		free(current_final->cmd);
	current_final->cmd = ft_strdup(current->value);
	if (current_final->cmd == NULL)
		return (2);
	return (0);
}

char	*concatenate_strings(const char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	return (result);
}

void	free_two_strings(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}
