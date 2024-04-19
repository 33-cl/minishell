/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:40:49 by maeferre          #+#    #+#             */
/*   Updated: 2023/11/28 16:27:43 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	int					result;
	const unsigned char	*char_s1;
	const unsigned char	*char_s2;

	i = 0;
	result = 0;
	char_s1 = s1;
	char_s2 = s2;
	while (i < n && result == 0)
	{
		result = char_s1[i] - char_s2[i];
		i++;
	}
	return (result);
}
