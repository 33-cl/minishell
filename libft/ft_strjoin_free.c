/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:52:00 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/08 20:04:52 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill_join(char *str, char *s1, char *s2, int nb_free)
{
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < len_s2)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (nb_free == 1 || nb_free == 3)
		free(s1);
	if (nb_free == 2 || nb_free == 3)
		free(s2);
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2, int nb_free)
{
	size_t		len_total;
	char		*str;

	if (!s1 || !s2)
		return (NULL);
	len_total = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len_total + 1));
	if (!str)
		return (NULL);
	return (ft_fill_join(str, s1, s2, nb_free));
}
