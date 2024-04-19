/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:44:58 by maeferre          #+#    #+#             */
/*   Updated: 2023/11/28 15:15:27 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*uc_s;

	i = 0;
	uc_s = (unsigned char *)s;
	while (uc_s[i] != (unsigned char)c)
	{
		if (uc_s[i] == '\0')
			return (NULL);
		i++;
	}
	return (&((char *)uc_s)[i]);
}
