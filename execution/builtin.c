/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:02:20 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/17 22:44:33 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Returns a bool indicating is the command is a builtin
*/

bool	is_a_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

/*
	Executes the right function based on the name of the command
	Returns the status of the execution
*/

bool	builtin_handler(t_cmd *command, t_env *env, int *status)
{
	if (!ft_strcmp(command->args[0], "echo"))
	{
		*status = 0;
		echo(command);
	}
	else if (!ft_strcmp(command->args[0], "cd"))
		*status = cd(command, env);
	else if (!ft_strcmp(command->args[0], "pwd"))
		*status = pwd(command);
	else if (!ft_strcmp(command->args[0], "export"))
		*status = export(command, env);
	else if (!ft_strcmp(command->args[0], "unset"))
		*status = unset(&env, command->args);
	else if (!ft_strcmp(command->args[0], "env"))
	{
		*status = 0;
		print_env(env);
	}
	return (*status != -1);
}

/*
	Executes the commande if it's a builtin
	Returns a bool if there is a dup2 error
*/

bool	exec_builtin(t_cmd *command, int *status, int *pipefd, t_env *env)
{
	int	old_stdout;

	command->exec = BUILTIN;
	if (command->next != NULL && !command->redir_out)
	{
		old_stdout = dup(STDOUT_FILENO);
		if (old_stdout == -1)
			return (false);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (close(pipefd[1]), false);
		close(pipefd[1]);
	}
	if (!builtin_handler(command, env, status))
		return (status);
	if (command->next != NULL)
	{
		if (dup2(old_stdout, STDOUT_FILENO) == -1)
			return (close(old_stdout), false);
		close(old_stdout);
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (close(pipefd[0]), -1);
		close(pipefd[0]);
	}
	return (true);
}
