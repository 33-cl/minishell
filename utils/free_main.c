/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:23:32 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/03 17:17:10 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_main(t_cmd **cmd, t_env **env, char **input)
{
	(void)cmd;
	if (*env)
		free_env(env);
	rl_clear_history();
	if (*input)
		free(*input);
}
