/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:14:47 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/15 17:41:11 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			t_size;

	t_size = (nmemb * size);
	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
	}
	else if (t_size / nmemb != size)
		return (NULL);
	else
	{
		ptr = malloc(t_size);
		if (!ptr)
			return (NULL);
		ft_bzero(ptr, t_size);
	}
	return (ptr);
}
