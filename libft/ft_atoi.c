/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:33:47 by maeferre          #+#    #+#             */
/*   Updated: 2023/11/29 13:43:17 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	const char	*ft_check_whitespace(const char *str)
{
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\r' || *str == '\f' || *str == '\v')
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	long int	result;
	int			sign;

	result = 0;
	sign = 1;
	str = ft_check_whitespace(str);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10;
		if (result < 0 && sign == 1)
			return (-1);
		if (result < 0 && sign == -1)
			return (0);
		result = result + (*str - '0');
		str++;
	}
	return (result * sign);
}
