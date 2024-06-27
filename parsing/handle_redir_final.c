/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_final.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:13:23 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/26 12:41:47 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*ok > $yes < $HOME > $"OK"'yes'

skip le $ si je suis dans uen redirection, est-ce que ce n'est pas execve
echo > $OME*/

#include "../minishell.h"

void	handle_redirection_processing(char *tmp, t_args *current, \
t_cmd **head_final_list, int *j)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = ft_strjoin(tmp, current->next->value);
	if (tmp2 == NULL)
	{
		(*head_final_list)->malloc_failed = true;
		free(tmp);
		return ;
	}
	process_delimiter(tmp2);
	tmp3 = remove_dollar_sign(tmp2);
	if (tmp3 == NULL)
	{
		(*head_final_list)->malloc_failed = true;
		free(tmp);
		free(tmp2);
		return ;
	}
	(*head_final_list)->redir[*j] = ft_strdup(tmp3);
	if ((*head_final_list)->redir[*j] == NULL)
		(*head_final_list)->malloc_failed = true;
	free(tmp2);
	free(tmp3);
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
	{
		handle_redirection_processing(tmp, current, head_final_list, j);
	}
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
		process_redirection("-", current, head_final_list, j);
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
	redir = ft_realloc_string_array_final((*head_final_list)->redir, (*j) + 2);
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

char	*remove_dollar_sign(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc(strlen(str) + 1);
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

bool	handle_delimiter_final(t_args **current, t_cmd **current_final, int *j)
{
	while ((*current)->quotes == 0 && (ft_strcmp((*current)->value, "<<") == 0 \
	|| ft_strcmp((*current)->value, ">>") == 0 || ft_strcmp((*current)->value, \
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
	if (*current != NULL && (*current)->type != 3)
		*current = (*current)->next;
	return (true);
}
