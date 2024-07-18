/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_until_delimiter.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:18:31 by odx               #+#    #+#             */
/*   Updated: 2024/07/18 15:58:28 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_line(char *result, char *line, int i, int *error)
{
	char	*temp;

	temp = result;
	if (i != 0)
	{
		result = ft_strjoin(result, "\n");
		free(temp);
		if (result == NULL)
			return (free(line), *error = 1, NULL);
	}
	temp = result;
	result = ft_strjoin(result, line);
	free(temp);
	free(line);
	if (result == NULL)
		return (*error = 1, NULL);
	return (result);
}

int	is_delimiter(char *line, char *delimiter, int len)
{
	if (line && ft_strncmp(line, delimiter, len) == 0 && \
		ft_strlen(delimiter) == ft_strlen(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

char	*handle_signal_and_eof(char *delimiter, char *result, int *error)
{
	char	*line;

	if (g_signal == 1)
		return (free(result), NULL);
	line = readline(">");
	if (!line)
	{
		line = ft_strdup(delimiter);
		printf("here-document delimited by end-of-file (wanted '%s')\n", \
		delimiter);
		if (!line)
			return (free(result), *error = 1, NULL);
	}
	return (line);
}

char	*read_line_until_delimiter(char *delimiter, int len, int *error)
{
	char	*line;
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (*error = 1, NULL);
	while (1)
	{
		line = handle_signal_and_eof(delimiter, result, error);
		if (!line)
			return (NULL);
		if (is_delimiter(line, delimiter, len))
			break ;
		result = handle_line(result, line, i, error);
		if (result == NULL)
			return (NULL);
		i++;
	}
	return (result);
}
