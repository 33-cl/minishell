/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:23:16 by maeferre          #+#    #+#             */
/*   Updated: 2023/11/28 16:27:32 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*char_s;

	i = 0;
	char_s = s;
	c = (unsigned char)c;
	while (i < n)
	{
		if ((unsigned char)char_s[i] == c)
			return ((unsigned char *)&char_s[i]);
		i++;
	}
	return (NULL);
}
