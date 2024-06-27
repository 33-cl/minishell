/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:38:30 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/25 16:17:24 by maeferre         ###   ########.fr       */
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
	print_env(current->next);
	printf("%s=%s\n", current->name, current->value);
	return (true);
}

/*
	Assigns "value" to the var "name" in the env
	Returns a bool for malloc() error
*/

bool	set_env(t_env **env, char *name, char *value)
{
	t_env	*current;
	t_env	*new_node;
	char	*new_value;

	if (!env || !name || !value)
		return (false);
	current = *env;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return (false);
			free(current->value);
			current->value = new_value;
			return (true);
		}
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (false);
	new_node->name = ft_strdup(name);
	if (!new_node->name)
		return (free(new_node), false);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (free(new_node->name), free(new_node), false);
	new_node->next = NULL;
	if (current == NULL)
		*env = new_node;
	else
		current->next = new_node;
	return (true);
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
		return (write(2, UNSET_NO_ARGS, 28), false);
	current = *env;
	prev = NULL;
	while (current->next != NULL)
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
				free(current);
				return (true);
			}
		}
		prev = current;
		current = current->next;
	}
	return (false);
}
