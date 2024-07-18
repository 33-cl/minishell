/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:55:24 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/17 22:33:05 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(t_env **env, char **args)
{
	int	i;
	int	temp_status;

	i = 1;
	while (args[i])
	{
		temp_status = set_env(env, args[i], NULL);
		if (!temp_status)
			return (0);
		i++;
	}
	return (0);
}
