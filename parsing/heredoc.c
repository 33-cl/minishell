/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:45:06 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/26 19:38:18 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Simulation d'un heredoc qui prend en parametres son delimiter
	et le fd dans lequel il doit ecrire
	
	>minishell$ <<delimiter cat
	> Hello world
	> blabla
	> delimiter
	Hello world
	blabla
segfault si des espaces apres un input dans le heredoc
Pour l'instant je n'ai pas les /n il faut les ajouter
Pour le path recup get path de mael
a l'interieur des heredoc il faut garder les guillemets
verifier les still reachable si je met un immense contenu dans un heredoc*/

//refaire tous les free dans heredoc

bool	process_heredoc_args(t_args *args)
{
	char	*heredoc_output;

	while (args != NULL)
	{
		if (args != NULL && args->prev != NULL && args->prev->value \
		!= NULL && ft_strcmp(args->prev->value, "<<") == 0)
		{
			heredoc_output = heredoc(args->value);
			if (!heredoc_output)
				return (false);
			if (args->value)
				free(args->value);
			args->value = ft_strdup(heredoc_output);
			if (!args->value)
				return (free(heredoc_output), false);
			free(heredoc_output);
		}
		args = args->next;
	}
	return (true);
}

bool	heredoc_init(t_command *command)
{
	t_command	*current;

	current = command;
	while (current)
	{
		if (!process_heredoc_args(current->args))
			return (false);
		current = current->next;
	}
	return (true);
}

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
			return (free(result), NULL);
		if (line && ft_strncmp(line, delimiter, len) == 0 && \
		ft_strlen(delimiter) == ft_strlen(line))
		{
			free(line);
			break ;
		}
		result = handle_line(result, line, i);
		if (result == NULL)
			return (NULL);
		i++;
	}
	return (result);
}

/*if (!line)-->dans ce cas la faut que je me comporte comme 
si je donnais eof-->line = delimiter
{
	line = ft_strdup(delimiter); // Simule l'entrée du délimiteur en cas d'EOF
	if (!line)
		return (free(result), NULL);--> a tester
}*/

char	*heredoc(char *delimiter)
{
	int		len;
	char	*result;

	len = ft_strlen(delimiter);
	if (len == 0)
		return (NULL);
	result = read_line_until_delimiter(delimiter, len);
	return (result);
}

bool	add_heredoc_delimiter(t_command *command, t_args *args)
{
	t_args		*current;
	int			i;

	current = args;
	i = 0;
	command->heredoc_delimiters = malloc(2 * sizeof(char *));
	if (command->heredoc_delimiters == NULL)
		return (false);
	command->heredoc_delimiters[0] = NULL;
	while (current != NULL)
	{
		if (current->prev != NULL && current->prev->value \
		!= NULL && ft_strcmp(current->prev->value, "<<") == 0)
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
		if ((*src != '\'' || in_double_quote) && \
		(*src != '\"' || in_single_quote))
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
			continue ;
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
