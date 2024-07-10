/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:01:52 by odx               #+#    #+#             */
/*   Updated: 2024/07/07 00:32:40 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	handle_tmp2_processing_heredoc(char *tmp, t_args *current, \
t_cmd **head_final_list, char **tmp2)
{
	*tmp2 = ft_strjoin(tmp, current->next->value);
	if (*tmp2 == NULL)
	{
		(*head_final_list)->malloc_failed = true;
		return (false);
	}
	return (true);
}

bool	handle_tmp3_processing_heredoc(char *tmp2, \
t_cmd **head_final_list, int *j)
{
	(*head_final_list)->redir[*j] = ft_strdup(tmp2);
	if ((*head_final_list)->redir[*j] == NULL)
	{
		(*head_final_list)->malloc_failed = true;
		free(tmp2);
		return (false);
	}
	return (true);
}

void	handle_redirection_processing_heredoc(char *tmp, t_args *current, \
t_cmd **head_final_list, int *j)
{
	char	*tmp2;

	if (!handle_tmp2_processing_heredoc(tmp, current, head_final_list, &tmp2))
		return ;
	if (!handle_tmp3_processing_heredoc(tmp2, head_final_list, j))
		return ;
	free(tmp2);
}

void	process_redirection_heredoc(char *str, t_args *current, \
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
		handle_redirection_processing_heredoc(tmp, current, head_final_list, j);
	else
	{
		(*head_final_list)->redir[*j] = ft_strdup(tmp);
		if ((*head_final_list)->redir[*j] == NULL)
			(*head_final_list)->malloc_failed = true;
	}
	free(tmp);
}
