/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:28:33 by maeferre          #+#    #+#             */
/*   Updated: 2023/11/17 16:28:33 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_string;
	size_t		i;
	size_t		len_s;

	i = 0;
	len_s = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((size_t)start > len_s)
		return (ft_strdup(""));
	if (len > len_s)
		len = len_s;
	if (len > len_s - start)
		len = len_s - start;
	new_string = malloc(sizeof(char) * (len + 1));
	if (!new_string)
		return (0);
	while (i < len)
	{
		new_string[i] = s[start + i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
