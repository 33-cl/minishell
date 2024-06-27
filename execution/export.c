/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:49:26 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/25 16:08:17 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Les noms de variables d'environnement sont soumis a certaines conditions
	Environnement variables names are restricted

	Authorized chars :

	first char  : A-Z a-z _
	other chars : A-Z a-z _ 0-9
*/

static bool	parsing_export(t_cmd *cmd, int nb_args)
{
	int		i;
	int		j;
	char	*error_msg;

	i = 0;
	while (i++, i < nb_args)
	{
		error_msg = ft_strjoin("export: `", cmd->args[i]);
		if (!((cmd->args[i][0] >= 'A' && cmd->args[i][0] <= 'Z') ||
			(cmd->args[i][0] >= 'a' && cmd->args[i][0] <= 'z') ||
			cmd->args[i][0] == '_'))
			return (print_error(NOT_VALID_ID, error_msg), false);
		j = 0;
		while (j++, cmd->args[i] && cmd->args[i][j] != '\0'
			&& cmd->args[i][j] != '=')
		{
			if (!((cmd->args[i][j] >= 'A' && cmd->args[i][j] <= 'Z') ||
				(cmd->args[i][j] >= 'a' && cmd->args[i][j] <= 'z') ||
				(cmd->args[i][j] >= '0' && cmd->args[i][j] <= '9') ||
				cmd->args[i][j] == '_'))
				return (print_error(NOT_VALID_ID, error_msg), false);
		}
		free(error_msg);
	}
	return (true);
}

/*
	Sorts the env in ascending order
*/

static t_env	*insert_sorted_desc(t_env *sorted, t_env *new_node)
{
	t_env	*current;

	if (!sorted || ft_strcmp(new_node->name, sorted->name) > 0)
	{
		new_node->next = sorted;
		if (sorted)
			sorted->prev = new_node;
		new_node->prev = NULL;
		return (new_node);
	}
	current = sorted;
	while (current->next && ft_strcmp(new_node->name, current->next->name) <= 0)
		current = current->next;
	new_node->next = current->next;
	if (current->next)
		current->next->prev = new_node;
	current->next = new_node;
	new_node->prev = current;
	return (sorted);
}

static t_env	*sort_env(t_env *env)
{
	t_env	*sorted;
	t_env	*current;
	t_env	*next;

	sorted = NULL;
	current = copy_env(env);
	if (!current)
		return (NULL);
	while (current)
	{
		next = current->next;
		current->next = NULL;
		current->prev = NULL;
		sorted = insert_sorted_desc(sorted, current);
		current = next;
	}
	free(current);
	return (sorted);
}

/*
	Reproduces export command

	Returns 0 by default
			1 if user error
		   -1 if malloc() error
*/

int	export(t_cmd *command, t_env *env)
{
	int		i;
	int		j;
	int		nb_args;
	char	*name;
	char	*value;

	(void)env;
	nb_args = ft_tablen(command->args);
	if (nb_args == 1)
	{
		if (!print_env(sort_env(env)))
			return (-1);
		return (0);
	}
	if (!parsing_export(command, nb_args))
		return (1);
	i = 0;
	while (i++, command->args[i])
	{
		j = 0;
		while (command->args[i][j] && command->args[i][j] != '=')
			j++;
		name = malloc(sizeof(char) * j + 1);
		if (!name)
			return (-1);
		ft_strlcpy(name, command->args[i], j + 1);
		value = ft_strchr(command->args[i], '=');
		if (value)
			value++;
		if (!set_env(&env, name, value))
			return (free(name), -1);
	}
	return (0);
}
