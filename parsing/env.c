/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:39:34 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/25 19:50:47 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	strtok_name_value(char **name, char **value, int i, char **envp)
{
	char	*equal_sign;

	equal_sign = ft_strchr(envp[i], '=');
	if (equal_sign == NULL)
		return (false);
	*name = ft_strndup(envp[i], equal_sign - envp[i]);
	if (*name == NULL)
		return (false);
	*value = ft_strdup(equal_sign + 1);
	if (*value == NULL)
	{
		free(*name);
		return (false);
	}
	return (true);
}

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

void	initialize_vars(int *i, t_env **current, char **name, char **value)
{
	*i = -1;
	*current = NULL;
	*name = NULL;
	*value = NULL;
}

void	free_resources(char *name, char *value, t_env **current)
{
	free(name);
	free(value);
	free_env(current);
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
