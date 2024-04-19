/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:29:42 by maeferre          #+#    #+#             */
/*   Updated: 2023/11/28 15:13:34 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*char_dest;
	const unsigned char	*char_src;

	i = 0;
	char_dest = dest;
	char_src = src;
	if (!dest && !src)
		return (NULL);
	if (char_dest > char_src)
	{
		while (n > 0)
		{
			char_dest[n - 1] = char_src[n - 1];
			n--;
		}
	}
	while (i < n && char_dest <= char_src)
	{
		char_dest[i] = char_src[i];
		i++;
	}
	return (dest);
}
