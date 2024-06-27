/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:10:51 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/25 14:02:46 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char *input)
{
	//gerer l'entre quote
	int		count;
	int		i;
	
	i = 0;
	count = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] != '\0')
		count++;
	while (input[i])
	{
		if (ft_is_space(input[i]) && !ft_is_space(input[i + 1]) && input[i + 1] != '\0')
			count++;
		i++;
	}
	return(count);
}

void	*ft_realloc_string_array(void *s, size_t size)
{
	char	*new_ptr;

	if (size == 0)
	{
		free(s);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	if (s != NULL)
	{
		ft_memcpy(new_ptr, s, size);
		free(s);
	}
	return (new_ptr);
}

void	*ft_realloc_old_size(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t copy_size;

    if (new_size == 0)
	{
        free(ptr);
        return (NULL);
    }
	new_ptr = malloc(new_size);
    if (new_ptr == NULL)
	{
		// free(ptr);//j' ai ajoute ca
        return (NULL);
	}
    if (ptr != NULL)
	{
        if (old_size < new_size)
            copy_size = old_size;
        else
            copy_size = new_size;
        ft_memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }
    return (new_ptr);
}

void	*ft_realloc(void *s, size_t size)
{
	char	*new_ptr;

	if (size == 0)
	{
		free(s);
		return (NULL);
	}
	new_ptr = malloc((size) * sizeof(char));
	if (new_ptr == NULL)
		return (NULL);
	if (s != NULL)
	{
		ft_memcpy(new_ptr, s, size);
		free(s);
	}
	return (new_ptr);
}

char	*ft_strtok_space(char *str)
{
	static char	*input = NULL;
	char		*result;
	bool		in_quote;
	char		quote_char;
	char		*delim;

	delim = " \t\n\r\v\f";
	in_quote = false;
	quote_char = 0;
	if (str != NULL)
		input = str;
	if (input == NULL)
		return (NULL);
	// Skip leading delimiters if outside of quotes
	while (*input && ft_is_space(*input) && !in_quote)
		input++;
	if (*input == '\0')
		return (NULL);
	
	result = handle_quote_strtok(&input, &in_quote, &quote_char, delim);
	return (result);
}


char	*handle_quote_strtok(char **input, bool *in_quote, char *quote_char, char *delim)
{
	char	*result;

	result = *input;
	while (**input)
	{
		if (!*in_quote && (**input == '\'' || **input == '\"'))
		{
			*in_quote = true;
			*quote_char = **input;
		}
		else if (*in_quote && **input == *quote_char && (*input == result || *(*input - 1) != '\\'))///maybe virer le input == result
			*in_quote = false;
		else if (!*in_quote && ft_strchr(delim, **input))
		{
			**input = '\0';
			(*input)++;
			break ;
		}
		(*input)++;
	}
	return (result);
}

char	*ft_strtok_pipe(char *str, char *delim)
{
	static char	*input = NULL;
	char		*result;
	bool		in_quote;
	char		quote_char;

	in_quote = false;
	quote_char = 0;
	if (str != NULL)
		input = str;
	if (input == NULL)
		return (NULL);
	// Skip leading delimiters if outside of quotes
	while (*input && ft_strchr(delim, *input) && !in_quote)
		input++;
	if (*input == '\0')
		return (NULL);
	result = handle_quote_strtok(&input, &in_quote, &quote_char, delim);
	return (result);
}

void	quote_status(bool *in_single_quote, bool *in_double_quote, char current_char)
{
	// virer la gestion d'echappement
	if (!*in_double_quote && current_char == '\'')
		*in_single_quote = !*in_single_quote;
	else if (!*in_single_quote && current_char == '\"')
		*in_double_quote = !*in_double_quote;
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	void	*ptr;

	if (s == NULL)
		return(NULL);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

