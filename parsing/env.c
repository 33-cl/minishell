/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:39:34 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/12 17:22:08 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool strtok_name_value(char **name, char **value, int i, char **envp)
{
	char	*equal_sign;

	equal_sign = ft_strchr(envp[i], '=');
	if (equal_sign == NULL)
		return false;
	*name = ft_strndup(envp[i], equal_sign - envp[i]);
	*value = ft_strdup(equal_sign + 1);
	if (*name == NULL || *value == NULL)
	{
		free(*name);
		free(*value);
		return false;
	}
	return true;
}

bool	malloc_set_name_value(t_env **new_node, char *name, char* value)
{
	*new_node = malloc(sizeof(t_env));
	if (!*new_node)
		return(false);
	(*new_node)->name = ft_strdup(name);
	(*new_node)->value = ft_strdup(value);
	return(true);
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*current;
	t_env	*new_node;
	char	*name;
	char	*value;

	i = -1;
	current = NULL;
	while (envp[++i] != NULL)
	{
		if (!strtok_name_value(&name, &value, i, envp))
			continue;
		if (!malloc_set_name_value(&new_node, name, value))
			return(current);
		if (!new_node->name || !new_node->value)
		{
			free(new_node);
			continue;
		}
		new_node->next = current;
		current = new_node;
	}
	return(current);
}

char	*get_env(t_env **env, char *name)
{
	t_env	*current;

	current = *env;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
			return(current->value);
		current = current->next;
	}
	return (NULL);
}

//segfault qund $ et qu'il trouve pas la suite