/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:38:36 by odx               #+#    #+#             */
/*   Updated: 2024/07/19 20:46:43 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_final_list(t_cmd **final_cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (*final_cmd == NULL)
		return ;
	current = *final_cmd;
	while (current->prev != NULL)
		current = current->prev;
	while (current != NULL)
	{
		next = current->next;
		free_single_cmd(current);
		current = next;
	}
	*final_cmd = NULL;
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	current = *env;
	while (current != NULL)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

void	free_expand(t_expand *exp)
{
	if (exp->result != NULL)
	{
		free(exp->result);
		exp->result = NULL;
	}
}

void	free_multi_quoted_args(t_args *arg)
{
	t_args	*multi_tmp;

	while (arg->multi_quoted_args != NULL)
	{
		multi_tmp = arg->multi_quoted_args;
		arg->multi_quoted_args = multi_tmp->next;
		free(multi_tmp->value);
		multi_tmp->value = NULL;
		free(multi_tmp);
		multi_tmp = NULL;
	}
}

void	free_args(t_args **args)
{
	t_args	*current;
	t_args	*tmp;

	current = *args;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		if (tmp->multi_quoted_args)
			free_multi_quoted_args(tmp);
		free(tmp);
	}
	*args = NULL;
}
