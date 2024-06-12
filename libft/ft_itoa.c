/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:33:51 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/12 16:40:36 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(long int n, size_t sign)
{
	size_t		len_str;

	len_str = sign;
	if (n == 0)
		len_str = 1;
	while (n > 0)
	{
		n = n / 10;
		len_str++;
	}
	return (len_str);
}

static char	*ft_fill(char *str, size_t len_str, long int n)
{
	size_t	i;

	i = 0;
	str[len_str] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[len_str - 1 - i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		len_str;
	long int	long_n;
	size_t		sign;

	long_n = n;
	sign = long_n < 0;
	if (sign == 1)
		long_n = -long_n;
	len_str = ft_count(long_n, sign);
	str = (char *)malloc(sizeof(char) * (len_str + 1));
	if (!str)
		return (NULL);
	if (sign == 1)
		str[0] = '-';
	str = ft_fill(str, len_str, long_n);
	return (str);
}
