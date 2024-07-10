/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_until_delimiter.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:18:31 by odx               #+#    #+#             */
/*   Updated: 2024/07/07 15:41:47 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*refaire les test des NULL
PROBLEME-> je supprime les single quote dans un heredoc
segfault si des espaces apres un input dans le heredoc
Pour l'instant je n'ai pas les /n il faut les ajouter
a l'interieur des heredoc il faut garder les guillemets
verifier les still reachable si je met un immense contenu dans un heredoc*/

char	*handle_line(char *result, char *line, int i)
{
	char	*temp;

	temp = result;
	if (i != 0)
	{
		result = ft_strjoin(result, "\n");
		free(temp);
		if (result == NULL)
			return (free(line), NULL);
	}
	temp = result;
	result = ft_strjoin(result, line);
	free(temp);
	free(line);
	if (result == NULL)
		return (NULL);
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

char	*read_line_until_delimiter(char *delimiter, int len)
{
	char	*line;
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			line = ft_strdup(delimiter);
			if (!line)
				return (free(result), NULL);
		}
		if (is_delimiter(line, delimiter, len))
			break ;
		result = handle_line(result, line, i);
		if (result == NULL)
			return (NULL);
		i++;
	}
	return (result);
}
