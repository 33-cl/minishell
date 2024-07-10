/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:31:34 by maeferre          #+#    #+#             */
/*   Updated: 2023/11/17 15:31:34 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_string;
	size_t	s_len;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s);
	new_string = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!new_string)
		return (NULL);
	while (i < s_len)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
