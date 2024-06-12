/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_final.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:13:23 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/12 17:24:54 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	add_specifier_to_struct(t_cmd **head_final_list, t_args *args, int *j)
{
	t_args	*current;
	char	**redir;

	current = args;
	if (!((*head_final_list)->redir))
	{
		(*head_final_list)->redir = malloc(sizeof(char *));
		if (!((*head_final_list)->redir))
			return (false);
		(*head_final_list)->redir[0] = NULL;
	}
	redir = ft_realloc_string_array_final((*head_final_list)->redir, (*j) + 2);// nouvel element + NULL
	if (!redir)
		return false;
	(*head_final_list)->redir = redir;
	if (ft_strcmp(current->value, "<<") == 0)
	{
		(*head_final_list)->redir[*j] = ft_strdup("-");
		(*head_final_list)->redir[*j] = ft_strjoin((*head_final_list)->redir[*j],current->next->value);
		(*j)++;
	}
	if (ft_strcmp(current->value, ">>") == 0)
	{
		(*head_final_list)->redir[*j] = ft_strdup("+");
		(*head_final_list)->redir[*j] = ft_strjoin((*head_final_list)->redir[*j],current->next->value);
		(*j)++;
	}
	if (ft_strcmp(current->value, ">") == 0)
	{
		(*head_final_list)->redir[*j] = ft_strdup(">");
		(*head_final_list)->redir[*j] = ft_strjoin((*head_final_list)->redir[*j],current->next->value);
		(*j)++;
	}
	if (ft_strcmp(current->value, "<") == 0)
	{
		(*head_final_list)->redir[*j] = ft_strdup("<");
		(*head_final_list)->redir[*j] = ft_strjoin((*head_final_list)->redir[*j],current->next->value);
		(*j)++;
	}
	return (true);
}


bool	handle_delimiter_final(t_args **current, t_cmd **current_final, int *j)
{
	if ((*current)->quotes == 0 && (ft_strcmp((*current)->value, "<<") == 0 || \
		ft_strcmp((*current)->value, ">>") == 0 || ft_strcmp((*current)->value,\
		"<") == 0 || ft_strcmp((*current)->value, ">") == 0))
	{
		process_specifier_args(&(*current), &(*current_final), &(*j));
			return (true);
	}
	return (false);
}

bool	process_specifier_args(t_args **current, t_cmd **current_final, int *j)
{
	add_specifier_to_struct(current_final, *current, j);
	*current = (*current)->next;
	if (*current != NULL)
		*current = (*current)->next;
	return (true);
}
