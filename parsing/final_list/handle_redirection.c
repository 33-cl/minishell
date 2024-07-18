/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:10:23 by odx               #+#    #+#             */
/*   Updated: 2024/07/18 15:04:34 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	handle_tmp2_processing(char *tmp, t_args *current, \
t_cmd **head_final_list, char **tmp2)
{
	*tmp2 = ft_strjoin(tmp, current->next->value);
	if (*tmp2 == NULL)
	{
		(*head_final_list)->malloc_failed = true;
		return (false);
	}
	process_delimiter(*tmp2);
	return (true);
}

bool	handle_tmp3_processing(char *tmp2, t_args *current, \
t_cmd **head_final_list, int *j)
{
	char	*tmp3;

	if (current->next && current->next->quotes == 0)
	{
		tmp3 = remove_dollar_sign(tmp2);
		if (tmp3 == NULL)
		{
			(*head_final_list)->malloc_failed = true;
			free(tmp2);
			return (false);
		}
		(*head_final_list)->redir[*j] = ft_strdup(tmp3);
		free(tmp3);
	}
	else
		(*head_final_list)->redir[*j] = ft_strdup(tmp2);
	if ((*head_final_list)->redir[*j] == NULL)
	{
		(*head_final_list)->malloc_failed = true;
		free(tmp2);
		return (false);
	}
	return (true);
}

char	*remove_dollar_sign(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '$')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
