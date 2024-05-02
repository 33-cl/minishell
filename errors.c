/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:11:59 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/30 17:51:14 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int type_error, char *str)
{
	if (type_error == FILE_NOT_FOUND)
		write(2, "minishell: no such file or directory: ", 38);
	else if (type_error == COMMAND_NOT_FOUND)
		write(2, "minishell: command not found : ", 31);

	if (str)
		write(1, str, ft_strlen(str));

	write(2, "\n", 1);
}