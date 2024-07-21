/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:23:32 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/21 17:56:16 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_main(t_cmd **cmd, t_env **env, char **input)
{
	(void)cmd;
	(void)input;
	if (*env)
		free_env(env);
	rl_clear_history();
	if (*input)
	{
		free(*input);
		*input = NULL;
	}
}

void	free_main_no_free_input(t_env **env)
{
	if (*env)
		free_env(env);
	rl_clear_history();
}

void	freee(t_cmd **final_cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (*final_cmd == NULL)
		return ;
	current = *final_cmd;
	while (current != NULL)
	{
		next = current->next;
		free_single_cmd(current);
		current = next;
	}
	*final_cmd = NULL;
}
