/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:46:10 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/18 15:05:19 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	char	**dup;
	size_t	i;
	size_t	len;

	if (tab == NULL)
		return (NULL);
	len = ft_tablen(tab);
	dup = (char **)malloc(sizeof(char *) * (len + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = ft_strdup(tab[i]);
		if (dup[i] == NULL)
		{
			while (i > 0)
				free(dup[--i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
