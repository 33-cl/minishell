/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:47:49 by maeferre          #+#    #+#             */
/*   Updated: 2023/11/29 13:48:21 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int					result;
	size_t				i;
	const unsigned char	*uc_s1;
	const unsigned char	*uc_s2;

	result = 0;
	i = 0;
	uc_s1 = (const unsigned char *)s1;
	uc_s2 = (const unsigned char *)s2;
	while (i < n && (uc_s1[i] != '\0' || uc_s2[i] != '\0'))
	{
		if (uc_s1[i] > uc_s2[i])
			return (uc_s1[i] - uc_s2[i]);
		else if (uc_s1[i] < uc_s2[i])
			return (uc_s1[i] - uc_s2[i]);
		i++;
	}
	return (result);
}
