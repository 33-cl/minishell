/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:45:06 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/12 17:27:57 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// /*
// 	Simulation d'un heredoc qui prend en parametres son delimiter
// 	et le fd dans lequel il doit ecrire
	
// 	>minishell$ <<delimiter cat
// 	> Hello world
// 	> blabla
// 	> delimiter
// 	Hello world
// 	blabla
// */


//segfault si des espaces apres un input dans le heredoc
// Pour l'instant je n'ai pas les /n il faut les ajouter

// Pour le path recup get path de mael
// a l'interieur des heredoc il faut garder les guillemets

bool	heredoc_init(t_command *command)
{
    t_command	*current = command;
    t_args		*args;
    char		*heredoc_output;
    // int			i;

    while (current)
	{
        // i = 0;
        args = current->args;
        while (args != NULL)
		{
            if (args != NULL && args->prev != NULL && args->prev->value != NULL && ft_strcmp(args->prev->value, "<<") == 0)
			{
                heredoc_output = heredoc(args->value);
                if (!heredoc_output)
				{
                    // Gérer l'erreur si heredoc_output est NULL
                    return (false); // Retourne une erreur
                }
                args->value = ft_strdup(heredoc_output);
                free(heredoc_output);
                // i++;
            }
            args = args->next;
        }
        current = current->next;
    }
    // if (i != current->nb_heredocs)
	// {
    //     // Gérer le cas où le nombre de heredocs trouvés ne correspond pas au nombre attendu
    //     return 1; // Retourne une erreur
    // }
    return (true); // Tout s'est bien passé
}

char	*heredoc(char *delimiter)
{
	char	*line;
	char	*result;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(delimiter);
	if (len == 0)
		return (NULL);
	result = ft_strdup("");
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			free(result);
			return (NULL);
		}
		//ici l'expand?
		if (line && ft_strncmp(line, delimiter, len) == 0 && ft_strlen(delimiter) == ft_strlen(line))//strlen + 1?
		{
			free(line);
			break;
		}
		if (i != 0)
			result = ft_strjoin(result, "\n");//le faire qu'au 2 eme appel
		result = ft_strjoin(result, line);
		free (line);
		i++;
	}
	return (result);
}

bool	add_heredoc_delimiter(t_command *command, t_args *args)
{
	t_args	*current;
	int			i;

	current = args;
	i = 0;
	command->heredoc_delimiters = malloc(2 * sizeof(char *));
	if (command->heredoc_delimiters == NULL)
		return (false);
	command->heredoc_delimiters[0] = NULL;
	while (current != NULL)
	{
		if (current->prev != NULL && current->prev->value != NULL && ft_strcmp(current->prev->value, "<<") == 0)
		{
			if (!realloc_temp(command, i))
				return (false);
			command->heredoc_delimiters[i] = current->value;
			i++;
			command->heredoc_delimiters[i] = NULL;
		}
		current = current->next;
	}
	return (true);
}

void	process_delimiter(char *delimiter)
{
	char	*src;
	char	*dst;
	bool	in_single_quote;
	bool	in_double_quote;

	src = delimiter;
	dst = delimiter;
	in_single_quote = false;
	in_double_quote = false;
	while (*src)
	{
		quote_status(&in_single_quote, &in_double_quote, *src);
		if ((*src != '\'' || in_double_quote) && (*src != '\"' || in_single_quote))
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

void	remove_quotes_in_delimiter(t_command *command)
{
	t_command	*current;
	int			i;

	current = command;
	while (current != NULL)
	{
		if (current->heredoc_delimiters == NULL)
		{
			current = current->next;
			continue;
		}
		i = 0;
		while (current->heredoc_delimiters[i])
		{
			if (current->heredoc_delimiters[i] != NULL)
				process_delimiter(current->heredoc_delimiters[i]);
			i++;
		}
		current = current->next;
	}
}

