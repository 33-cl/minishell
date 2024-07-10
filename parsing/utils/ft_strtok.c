/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:03:50 by debian            #+#    #+#             */
/*   Updated: 2024/07/08 20:03:51 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	while (*input && ft_is_space(*input) && !in_quote)
		input++;
	if (*input == '\0')
		return (NULL);
	result = handle_quote_strtok(&input, &in_quote, &quote_char, delim);
	return (result);
}

char	*handle_quote_strtok(char **input, bool *in_quote, \
char *quote_char, char *delim)
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
		else if (*in_quote && **input == *quote_char && \
		(*input == result || *(*input - 1) != '\\'))
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
	while (*input && ft_strchr(delim, *input) && !in_quote)
		input++;
	if (*input == '\0')
		return (NULL);
	result = handle_quote_strtok(&input, &in_quote, &quote_char, delim);
	return (result);
}

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
