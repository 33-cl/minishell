/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:44:20 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/22 05:30:08 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Assigns "value" to the var "name" in the env
	Returns a bool for malloc() error
*/

static t_env	*create_new_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	if (!new_node->name)
		return (free(new_node), NULL);
	if (!value)
		new_node->value = ft_strdup("");
	else
		new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (free(new_node->name), free(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

static bool	update_env_value(t_env *current, char *name, char *value)
{
	char	*new_value;

	if (ft_strcmp(current->name, name) == 0)
	{
		if (!value)
		{
			new_value = ft_strdup("");
			if (!new_value)
				return (false);
		}
		else
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return (false);
		}
		free(current->value);
		current->value = new_value;
		return (true);
	}
	return (false);
}

bool	set_env_export(t_env **env, char *name, char *value)
{
	t_env	*current;
	t_env	*new_node;

	if (!env || !name)
		return (false);
	if (!value)
		return (true);
	current = *env;
	while (current != NULL)
	{
		if (update_env_value(current, name, value))
			return (true);
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	new_node = create_new_node(name, value);
	if (!new_node)
		return (false);
	if (current == NULL)
		*env = new_node;
	else
		current->next = new_node;
	return (true);
}

bool	set_env(t_env **env, char *name, char *value)
{
	t_env	*current;
	t_env	*new_node;

	if (!env || !name)
		return (false);
	current = *env;
	while (current != NULL)
	{
		if (update_env_value(current, name, value))
			return (true);
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	new_node = create_new_node(name, value);
	if (!new_node)
		return (false);
	if (current == NULL)
		*env = new_node;
	else
		current->next = new_node;
	return (true);
}
