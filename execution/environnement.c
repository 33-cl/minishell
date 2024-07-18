/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:38:30 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/17 23:28:32 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Returns a copy of the environnement
*/

t_env	*copy_env(t_env *env)
{
	t_env	*new_node;

	if (!env)
		return (NULL);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = strdup(env->name);
	new_node->value = strdup(env->value);
	new_node->next = copy_env(env->next);
	if (new_node->next)
		new_node->next->prev = new_node;
	new_node->prev = NULL;
	return (new_node);
}

/*
	Displays the environnement
*/

bool	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	if (current == NULL)
		return (false);
	if (current->next)
		print_env(current->next);
	if (current->name && current->value && current->value[0])
		printf("%s=%s\n", current->name, current->value);
	return (true);
}

bool	print_env_reverse(t_env *env)
{
	t_env	*current;

	current = env;
	if (current == NULL)
		return (false);
	while (current != NULL)
	{
		if (current->name && current->value && current->value[0])
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (true);
}

/*
	Resets an env var to NULL
*/

static	void	reset_var(t_env **var)
{
	(*var)->name = NULL;
	(*var)->value = NULL;
	*var = NULL;
}

/*
	Deletes the var called "name"
	Returns a bool for malloc() error
*/

bool	unset_env(t_env **env, char *name)
{
	t_env	*current;
	t_env	*prev;

	if (!name)
		return (write(2, UNSET_NO_ARGS, 28), true);
	current = *env;
	prev = NULL;
	while (current != NULL && current->name)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
			{
				*env = current->next;
				free(current->name);
				free(current->value);
				return (free(current), reset_var(&current), false);
			}
		}
		prev = current;
		current = current->next;
	}
	return (false);
}
