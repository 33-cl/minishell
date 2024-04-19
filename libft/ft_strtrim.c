/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 21:33:58 by maeferre          #+#    #+#             */
/*   Updated: 2023/11/17 21:33:58 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill1(char *str, size_t min, size_t max, char const *s1)
{
	size_t	i;

	i = 0;
	if (!str || !s1)
		return (NULL);
	while (min + i < max)
	{
		str[i] = s1[min + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_alloc_sizeone(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	min;
	size_t	max;

	min = 0;
	max = ft_strlen(s1);
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (ft_strchr(set, s1[min]) && s1[min])
	{
		min++;
		if (min == max)
		{
			return (ft_alloc_sizeone());
		}
	}
	while (ft_strchr(set, s1[max - 1]) && max > 0)
		max--;
	str = (char *)malloc(sizeof(char) * (max - min + 1));
	return (ft_fill1(str, min, max, s1));
}
