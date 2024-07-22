/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isallspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 02:50:44 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/22 05:29:48 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isallspace(char *str)
{
	size_t	i;

	i = -1;
	while (i++, str[i])
		if (!ft_is_space(str[i]))
			return (false);
	return (true);
}
