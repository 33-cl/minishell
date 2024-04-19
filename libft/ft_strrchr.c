/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:28:16 by maeferre          #+#    #+#             */
/*   Updated: 2023/11/28 15:48:05 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			size;
	unsigned char	*uc_s;

	size = ft_strlen(s);
	uc_s = (unsigned char *)s;
	while (uc_s[size] != (unsigned char)c)
	{
		if (size == 0)
			return (NULL);
		size--;
	}
	return (&((char *)uc_s)[size]);
}
