/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:32:34 by odx               #+#    #+#             */
/*   Updated: 2024/07/17 20:38:48 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_unquoted_arg(t_args *current, t_cmd *current_final, int *i)
{
	if (current_final->cmd)
	{
		free(current_final->cmd);
		current_final->cmd = NULL;
	}
	current_final->args[*i] = ft_strdup(current->value);
	if (current_final->args[*i] == NULL)
		return (2);
	current_final->cmd = ft_strdup(current_final->args[0]);
	if (current_final->cmd == NULL)
		return (2);
	(*i)++;
	return (0);
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
		if ((str[i] == '\'' && current->quotes != 2) || \
		(str[i] == '\"' && current->quotes != 1))
		{
			i++;
			continue ;
		}
		result[j] = str[i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	process_quoted_arg(t_args *current, t_cmd *current_final, int *i)
{
	char	*unquoted_result;

	unquoted_result = ft_unquote_result(current->value, current);
	if (unquoted_result == NULL)
		return (2);
	current_final->args[*i] = ft_strdup(unquoted_result);
	if (current_final->args[*i] == NULL)
	{
		free(unquoted_result);
		return (2);
	}
	free(unquoted_result);
	(*i)++;
	return (0);
}
