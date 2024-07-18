/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_specifier_to_struct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:47:02 by odx               #+#    #+#             */
/*   Updated: 2024/07/17 20:27:06 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_redirection_processing(char *tmp, t_args *current, \
t_cmd **head_final_list, int *j)
{
	char	*tmp2;

	if (!handle_tmp2_processing(tmp, current, head_final_list, &tmp2))
		return ;
	if (!handle_tmp3_processing(tmp2, current, head_final_list, j))
		return ;
	free(tmp2);
}

void	process_redirection(char *str, t_args *current, \
t_cmd **head_final_list, int *j)
{
	char	*tmp;

	tmp = ft_strdup(str);
	if (tmp == NULL)
	{
		(*head_final_list)->malloc_failed = true;
		return ;
	}
	if (current->next && current->next->type != 3)
		handle_redirection_processing(tmp, current, head_final_list, j);
	else
	{
		(*head_final_list)->redir[*j] = ft_strdup(tmp);
		if ((*head_final_list)->redir[*j] == NULL)
			(*head_final_list)->malloc_failed = true;
	}
	free(tmp);
}

void	handle_redirection(t_args *current, t_cmd **head_final_list, int *j)
{
	if (ft_strcmp(current->value, "<<") == 0)
		process_redirection_heredoc("-", current, head_final_list, j);
	else if (ft_strcmp(current->value, ">>") == 0)
		process_redirection("+", current, head_final_list, j);
	else if (ft_strcmp(current->value, ">") == 0)
		process_redirection(">", current, head_final_list, j);
	else if (ft_strcmp(current->value, "<") == 0)
		process_redirection("<", current, head_final_list, j);
	(*j)++;
}

bool	add_specifier_to_struct(t_cmd **head_final_list, t_args *args, int *j)
{
	t_args	*current;
	char	**redir;

	current = args;
	if (!((*head_final_list)->redir))
	{
		(*head_final_list)->redir = malloc(sizeof(char *));
		if (!((*head_final_list)->redir))
			return ((*head_final_list)->malloc_failed = true, false);
		(*head_final_list)->redir[0] = NULL;
	}
	redir = ft_realloc_string_array_final_bis \
	((*head_final_list)->redir, (*j) + 2);
	if (!redir)
	{
		(*head_final_list)->malloc_failed = true;
		return (false);
	}
	(*head_final_list)->redir = redir;
	if (current && (ft_strcmp(current->value, ">") == 0 || \
	ft_strcmp(current->value, "<") == 0 || ft_strcmp(current->value, ">>") \
	== 0 || ft_strcmp(current->value, "<<") == 0))
		handle_redirection(current, head_final_list, j);
	return (true);
}
