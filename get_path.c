/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:42:56 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/17 16:55:19 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fill_path(char *path, char **possible_paths, char *command, int i)
{
	ft_strcpy(path, possible_paths[i]);
	ft_strcat(path, "/");
	ft_strcat(path, command);
	return (path);
}

char	*get_path(char *command, char **env)
{
	size_t	i;
	char	*path;
	char	**paths;

	i = 0;
	if (!env || !*env)
		return (NULL);
	while (ft_strncmp(env[i], "PATH", 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (ft_free_tab(paths), NULL);
	i = -1;
	while (i++, paths[i])
	{
		path = malloc(sizeof(char) + ft_strlen(paths[i])
				+ ft_strlen(command) + 2);
		if (!path)
            return (ft_free_tab(paths), NULL);
		path = fill_path(path, paths, command, i);
		if (!access(path, F_OK))
			return (ft_free_tab(paths), path);
		free(path);
	}
	return (ft_free_tab(paths), NULL);
}