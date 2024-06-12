/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:28:02 by qordoux           #+#    #+#             */
/*   Updated: 2024/05/29 19:58:42 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//LA OU JE CREE MES NOEUDS, J'AJOUTE UN CHECK DES QUOTE A L'INTERIEUR DE CHAQUE NOEUD

bool	need_add_spaces_redir(bool in_single_quote, bool in_double_quote, char *input, int i)
{
	if (in_double_quote || in_single_quote)
		return (false);
	if (input[i + 1] == '|' || (i >= 1 && input[i] == '|'))
		return (true);
	// if (input[i] == '|' && input[i + 1] != ' ' && input[i + 1] != '\0')
	// 	return (true);
	if (i >= 1 && input[i] == '>' && input[i - 1] == '>')
		if (input[i + 1] != ' ')
			return (true); // Nécessite un espace après ">>"
	if (i >= 2 && input[i] == '<' && input[i - 1] == '<' && input[i - 2] == '<')
		if (input[i + 1] != ' ')
			return (true); // Nécessite un espace après ">>"
	return (false);
}
bool	need_add_spaces(bool in_single_quote, bool in_double_quote, char *input, int i)
{
	if (in_double_quote || in_single_quote)
		return (false);
	if (i > 0 && (((input[i + 1] == '>' && input[i] != '>') || \
	(input[i + 1] == '<' && input[i] != '<') || input[i + 1] == '|') && input[i] != ' '))
		return (true);
	// else if (!in_single_quote && !in_double_quote && ((input[i] == '>' && 
	// input[i + 1] != '>' && input[i + 1] != ' ' && input[i + 1] != '\0') ||
	// (input[i] == '<' && input[i + 1] != '<' && 
	// input[i + 1] != ' ' && input[i + 1] != '\0') || 
	// (input[i] == '|' && input[i + 1] != ' ' && input[i + 1] != '\0')))
	// 	return (true);
	return (false);
}

char	*put_space_before_redir(char *input, int i)
{
	int		len;
	char	*new_str;
	bool	in_single_quote;
	bool	in_double_quote;
	char	prev_char;

	prev_char = '\0';
	in_single_quote = false;
	in_double_quote = false;
	new_str = realloc_for_more_space(input, prev_char, in_single_quote, \
	in_double_quote);
	len = 0;
	while (input[++i])
	{
		quote_status(&in_single_quote, &in_double_quote, input[i]);
		new_str[len++] = input[i];
		if (need_add_spaces(in_single_quote, in_double_quote, input, i))
			new_str[len++] = ' ';
		if (need_add_spaces_redir(in_single_quote, in_double_quote, new_str, len - 1))
			new_str[len++] = ' ';
		if (!in_single_quote && !in_double_quote && input[i] == '>' && input[i + 1] != '>' && input[i + 1] != ' ')
			new_str[len++] = ' ';
		if (!in_single_quote && !in_double_quote && input[i] == '<' && input[i + 1] != '<' && input[i + 1] != ' ')
			new_str[len++] = ' ';
		if (!in_single_quote && !in_double_quote && input[i + 1] && input[i + 1] == '|' && input[i] != ' ')
			new_str[len++] = ' ';
		if (input[i] == '|' && input[i + 1] != ' ' && input[i + 1] != '\0')
			new_str[len++] = ' ';
		prev_char = input[i];
	}
	new_str[len] = '\0';
	return (new_str);
}
//cette fonction devrais fonctionner en enlevant les commentaires je les garde au cas ou 
bool	count_when_need_space(bool in_single_quote, bool in_double_quote, char *input, int i)
{
	// if (input[i] == '\0')
	// 	return (true);
	// if (input[i + 1] == '\0')
	// 	return (true);
	if (!in_double_quote && !in_single_quote && (((input[i] == '>' && \
		input[i + 1] != '>') || \
		(input[i] == '<' && input[i + 1] != '<')) && input[i + 1] != ' ') && \
		input[i + 1] != '\0')
		return (true);
	else if (i > 0 && !in_double_quote && !in_single_quote && (((input[i] == '>' && \
		input[i - 1] != '>') || \
		(input[i] == '<' && input[i - 1] != '<')) && input[i - 1] != ' '))
		return (true);
	else if ((input[i] == '|' && input[i + 1] != ' ' && input[i + 1] != '\0') || 
		(i > 0 && input[i] == '|' && input[i - 1] != ' '))
			return (true);
	else if (i >= 1 && !in_double_quote && !in_single_quote && input[i] == '>' && input[i + 1] == '>' && input[i + 2] != ' ')
		return (true);
	if (input[i] == '>' && input[i + 1] != '>' && input[i + 1] != ' ')
		return (true);
	if (input[i] == '<' && input[i + 1] != '<' && input[i + 1] != ' ')
		return (true);
	if (need_add_spaces(in_single_quote, in_double_quote, input, i))
		return (true);
	if (need_add_spaces_redir(in_single_quote, in_double_quote, input, i))
		return (true);
	if (input[i] == '>' && input[i + 1] != '>' && input[i + 1] != ' ')
		return (true);
	if (input[i] == '<' && input[i + 1] != '<' && input[i + 1] != ' ')
		return (true);
	return (false);
}

char	*realloc_for_more_space(char *input, char prev_char, \
bool in_single_quote, bool in_double_quote)
{
	//je n'utilise plus prevchar
	int			i;
	int			len;
	int			count;
	char		*new_str;

	(void)prev_char;
	prev_char = '\0';
	in_single_quote = false;
	in_double_quote = false;
	count = 0;
	len = ft_strlen(input) + 1;
	i = -1;
	while (input[++i])
	{
		quote_status(&in_single_quote, &in_double_quote, input[i]);
		if (count_when_need_space(in_single_quote, in_double_quote, input, i))
			count += 2;
		prev_char = input[i];
	}
	new_str = ft_calloc(((len + count + 1)), sizeof(char));
	if (!new_str)
		return (NULL);
	return (new_str);
}
