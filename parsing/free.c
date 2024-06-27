/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:19:48 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/26 16:41:43 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_args_global(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}

void	free_redir(char **redir)
{
	int	i;

	if (redir == NULL)
		return ;
	i = 0;
	while (redir[i] != NULL)
	{
		free(redir[i]);
		i++;
	}
	free(redir);
}

void	free_single_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
		free_args_global(cmd->args);
	if (cmd->redir)
		free_redir(cmd->redir);
	free(cmd);
}

void	free_final_list(t_cmd **final_cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (*final_cmd == NULL)
		return ;
	current = *final_cmd;
	while (current != NULL)
	{
		next = current->next;
		free_single_cmd(current);
		current = next;
	}
	*final_cmd = NULL;
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	current = *env;
	while (current != NULL)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

void	free_expand(t_expand *exp)
{
	if (exp->result != NULL)
	{
		free(exp->result);
		exp->result = NULL;
	}
}

void	free_args(t_args **args)
{
	t_args	*current;
	t_args	*multi_tmp;
	t_args	*tmp;

	current = *args;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		if (tmp->multi_quoted_args)
		{
			multi_tmp = tmp->multi_quoted_args;
			while (multi_tmp != NULL)
			{
				tmp->multi_quoted_args = multi_tmp->next;
				free(multi_tmp->value);
				multi_tmp->value = NULL;
				free(multi_tmp);
				multi_tmp = NULL;
				multi_tmp = tmp->multi_quoted_args;
			}
		}
		free(tmp);
	}
	*args = NULL;
}

void	free_heredoc_delimiters(char **heredoc_delimiters)
{
	int	i;

	i = 0;
	while (heredoc_delimiters[i] != NULL)
	{
		free(heredoc_delimiters[i]);
		heredoc_delimiters[i] = NULL;
		i++;
	}
	free(heredoc_delimiters);
}

void	free_redirections(char **redir)
{
	int	i;

	i = 0;
	while (redir[i] != NULL)
	{
		free(redir[i]);
		i++;
	}
	free(redir);
}

void	free_command(t_command **command)
{
	t_command	*current;
	t_command	*next;

	current = *command;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->args)
			free_args(&current->args);
		if (current->heredoc_delimiters)
			free_heredoc_delimiters(current->heredoc_delimiters);
		if (current->redir)
			free_redirections(current->redir);
		free(current);
		current = next;
	}
	*command = NULL;
}
void	free_command_before(t_command **command)
{
	t_command	*current;
	t_command	*next;

	current = *command;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->args)
			free_args(&current->args);
		if (current->heredoc_delimiters)
			free(current->heredoc_delimiters);
		if (current->redir)
			free_redirections(current->redir);
		free(current);
		current = next;
	}
	*command = NULL;
}