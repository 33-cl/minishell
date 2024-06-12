/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:58:06 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/07 14:00:46 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_len(t_cmd *command)
{
	int	len;

	if (command->args[0] == NULL)
		return (0);
	len = 1;
	while (command->next != NULL)
	{
		len++;
		command = command->next;
	}
	return (len);
}
