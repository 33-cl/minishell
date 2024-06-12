/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_or_not_final.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:09:46 by qordoux           #+#    #+#             */
/*   Updated: 2024/05/23 22:32:12 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//stocker le dernier heredoc dans un fichier avec putstr_fd et stocker son fd 

bool	process_quoted_or_unquoted(t_args *current, t_cmd *current_final, int *i)
{
	if (current->multi_quoted_args)
	{
		if (!(process_multi_quoted_args(current, current_final, &(*i))))
			return (false);
	}
	else
	{
		if (!(process_unquoted_args(current, current_final, &(*i))))
			return (false);
	}
	return (true);
}

bool	process_multi_quoted_args(t_args *current, t_cmd *current_final, int *i)
{
    t_args	*current_multi_quoted_args;

	current_multi_quoted_args = current->multi_quoted_args;
    handle_multi_quoted_args(current_multi_quoted_args, current, current_final, i);
	return (true);
}

bool	process_unquoted_args(t_args *current, t_cmd *current_final, int *i)
{
    char	*unquoted_result;
	int		len;

	if (current->type == 0)
		current_final->cmd = ft_strdup(current->value);
	len = ft_lstsize_final(current);
    current_final->args = ft_realloc_string_array_final(current_final->args, len + 1);
    if (current->quotes != 0 && (current->prev == NULL || ft_strcmp(current->prev->value, "<<") != 0))
	{
        unquoted_result = ft_unquote_result(current->value, current);
        current_final->args[*i] = ft_strdup(unquoted_result);
	}
    else
	{
        current_final->args[*i] = ft_strdup(current->value);
		current_final->cmd = ft_strdup(current_final->args[0]);
	}
    (*i)++;
	// current_final->args[*i] = NULL;
	return (true);
}

//retoucher la fonction du dessous, plus besoin de current

bool	handle_multi_quoted_args(t_args	*current_multi_quoted_args, t_args *current, t_cmd *current_final, int *i)
{
	char	*new_str;
	char	*temp;
	char	*new_temp;

	(void)current;
	temp = ft_strdup("");
	while (current_multi_quoted_args != NULL)
	{
		// if (current->type == 0)
		// 	current_final->cmd = ft_strdup(current->multi_quoted_args->value);//cela
		new_str = ft_strdup(current_multi_quoted_args->value);
		new_temp = ft_strjoin(temp, new_str);
		free(temp);
		temp = new_temp;
		free(new_str);
		current_multi_quoted_args = current_multi_quoted_args->next;
	}
	current_final->args[*i] = temp;
	(*i)++;
	current_final->args[*i] = NULL;
	current_final->cmd = ft_strdup(current_final->args[0]);
	return (true);
}

char	*ft_unquote_result(char *str, t_args *current)
{
	int		len;
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' && current->quotes != 2) || (str[i] == '\"' && current->quotes != 1))
		{
			i++;
			continue;
		}
		result[j] = str[i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}

// char	*ft_unquote_result(char	*str, t_args *current)
// {
// 	int		len;
// 	char	*result;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	len = ft_strlen(str);// ici avant j'avais -2 car -1 par quote, cette fonction est surement a revoir
// 	result = malloc(sizeof(char) * len + 1);
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && current->quotes != 2)
// 			i++;
// 		if (str[i] == '\"' && current->quotes != 1)
// 			i++;
// 		result[j] = str[i];
// 		j++;
// 		i++;
// 	}
// 	result[j] = '\0';
// 	return (result);
// }