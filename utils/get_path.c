/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:42:56 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/17 14:12:50 by maeferre         ###   ########.fr       */
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

static	char	*get_path(char *command, char **env, size_t i)
{
	char	*path;
	char	**paths;

	i = -1;
	if (!env || !*env)
		return (NULL);
	while (i++, ft_strncmp(env[i], "PATH", 4))
		if (!env[i + 1])
			return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (ft_free_tab(paths), exit(EXIT_FAILURE), NULL);
	i = -1;
	while (i++, paths[i])
	{
		path = malloc(sizeof(char) + ft_strlen(paths[i])
				+ ft_strlen(command) + 2);
		if (!path)
			return (ft_free_tab(paths), exit(EXIT_FAILURE), NULL);
		path = fill_path(path, paths, command, i);
		if (!access(path, F_OK))
			return (ft_free_tab(paths), path);
		free(path);
	}
	return (ft_free_tab(paths), NULL);
}

bool	get_command(char *command, char **env, char **path)
{
	if (ft_strchr(command, '/'))
	{
		*path = ft_strdup(command);
		return (*path);
	}
	else
	{
		*path = get_path(command, env, -1);
		return (*path);
	}
}
