/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_get_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:22:20 by odx               #+#    #+#             */
/*   Updated: 2024/07/17 20:32:11 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	malloc_set_name_value(t_env **new_node, char *name, char *value)
{
	*new_node = malloc(sizeof(t_env));
	if (!*new_node)
		return (false);
	(*new_node)->name = ft_strdup(name);
	if (!(*new_node)->name)
	{
		free(*new_node);
		return (false);
	}
	(*new_node)->value = ft_strdup(value);
	if (!(*new_node)->value)
	{
		free((*new_node)->name);
		free(*new_node);
		return (false);
	}
	if (name)
		free(name);
	if (value)
		free(value);
	return (true);
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*current;
	t_env	*new_node;
	char	*name;
	char	*value;

	initialize_vars(&i, &current, &name, &value);
	while (envp[++i] != NULL)
	{
		if (!strtok_name_value(&name, &value, i, envp))
			return (free_env(&current), NULL);
		if (!malloc_set_name_value(&new_node, name, value))
		{
			free_resources(name, value, &current);
			return (current);
		}
		if (!new_node->name || !new_node->value)
		{
			free (new_node);
			continue ;
		}
		new_node->next = current;
		current = new_node;
	}
	return (current);
}

char	*get_env(t_env **env, char *name)
{
	t_env	*current;

	current = *env;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
