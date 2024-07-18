/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:42:56 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/18 16:35:00 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*fill_path(char *path, char **possible_paths, char *command, int i)
{
	ft_strcpy(path, possible_paths[i]);
	ft_strcat(path, "/");
	ft_strcat(path, command);
	return (path);
}

static	int	get_path(char *command, char **env, char **path)
{
	char	**paths;
	size_t	i;

	i = -1;
	if (!env || !*env)
		return (0);
	while (i++, ft_strncmp(env[i], "PATH", 4))
		if (!env[i + 1])
			return (0);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (ft_free_tab(paths), -1);
	i = -1;
	while (i++, paths[i])
	{
		*path = malloc(sizeof(char)
				+ ft_strlen(paths[i]) + ft_strlen(command) + 2);
		if (!*path)
			return (ft_free_tab(paths), -1);
		*path = fill_path(*path, paths, command, i);
		if (!access(*path, F_OK))
			return (ft_free_tab(paths), 1);
		free(*path);
	}
	return (ft_free_tab(paths), 0);
}

int	get_command(char *command, char **env, char **path)
{
	int		return_value;

	if (ft_strchr(command, '/'))
	{
		*path = ft_strdup(command);
		if (*path == NULL)
			return (-1);
		return (1);
	}
	else
	{
		return_value = get_path(command, env, path);
		if (return_value == 0)
		{
			*path = NULL;
		}
		return (return_value);
	}
}
