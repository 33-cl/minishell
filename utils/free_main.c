/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:23:32 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/26 16:27:48 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_main(t_cmd **cmd, t_env **env, char **input)
{
	// if (*cmd)
	// 	free_final_list(cmd);
	(void)cmd;
	if (*env)
		free_env(env);
	rl_clear_history();
	if (*input)
		free(*input);
}
