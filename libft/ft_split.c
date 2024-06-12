/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 00:18:58 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/12 18:08:26 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_word(char const *s, char c)
{
	size_t		length;

	length = 0;
	while (*s && *s != c)
	{
		length++;
		s++;
	}
	return (length);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	i;
	size_t	nb_strings;

	i = 0;
	nb_strings = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		nb_strings++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (nb_strings);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	nb_strings;
	size_t	i;

	if (!s)
		return (NULL);
	nb_strings = ft_count_word(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_strings + 1));
	if (!tab)
		return (NULL);
	tab[nb_strings] = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			tab[i] = ft_substr(s, 0, ft_len_word(s, c));
			if (!tab[i++])
				return (ft_free_tab(tab), NULL);
			s += ft_len_word(s, c);
		}
		else
			s++;
	}
	return (tab);
}
