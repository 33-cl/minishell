/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:16:24 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/22 03:53:51 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Reproduces pwd command
	Returns 1 is getcwd() error
*/

int	pwd(t_cmd *cmd)
{
	char	*cwd;

	if (ft_tablen(cmd->args) >= 2
		&& (ft_strlen(cmd->args[1]) >= 2 && cmd->args[1][0] == '-') &&
		!(ft_strlen(cmd->args[1]) == 2 && cmd->args[1][0] == '-' &&
		cmd->args[1][1] == '-'))
	{
		ft_putstr_fd("minishell: pwd ", 2);
		ft_putchar_fd(cmd->args[1][0], 2);
		ft_putchar_fd(cmd->args[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
