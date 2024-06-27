/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:28:29 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/26 19:14:16 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Executes the command if its not a builtin and the redirections are handled 
*/

int	ft_execve(t_cmd *cmd, t_env *env, int status)
{
	char	*path;
	char	**final_env;

	final_env = t_env_to_array(env);
	free_env(&env);
	if (!final_env)
		exit(-1);
	get_command(cmd->args[0], final_env, &path);
	if (path)
	{
		execve(path, cmd->args, final_env);
		if (cmd->args[0][0] == '.' && !cmd->args[0][1] && !cmd->args[1])
			status = print_error(ARGUMENT_REQUIRED, cmd->args[0]);
		else if (is_a_dir(cmd->args[0]))
			status = print_error(IS_A_DIRECTORY, cmd->args[0]);
		else if (!access(path, F_OK))
			status = print_error(PERMISSION_DENIED, cmd->args[0]);
		else
			status = print_error(FILE_NOT_FOUND, cmd->args[0]);
		return (free_final_list(&cmd), free(path), ft_free_tab(final_env), exit(status), 0);
	}
	if (!((cmd->args[0][0] == ':' || cmd->args[0][0] == '!' || cmd->args[0][0]
		== '#') && !cmd->args[0][1] && !cmd->args[1]) && cmd->args[0][0])
		status = print_error(COMMAND_NOT_FOUND, cmd->args[0]);
	return (free_final_list(&cmd), ft_free_tab(final_env), exit(status), 0);
}

/*
	Executes the command if it's not a builtin
	Returns a bool for function() error
*/

bool	exec_execve(pid_t *pid, t_cmd *command, int *pipefd, t_env *env, t_streams *std, int i)
{
	command->exec = EXECVE;
	*pid = fork();
	if (*pid == -1)
		return (false);
	if (*pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		free(pid - i);
		close(std->in);
		close(std->out);
		if (command->next != NULL && !command->redir_out)
		{
			close(pipefd[0]);
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				return (close(pipefd[1]), false);
			close(pipefd[1]);
		}
		ft_execve(command, env, 0);
	}
	if (command->next != NULL)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (close(pipefd[0]), false);
		close(pipefd[0]);
	}
	return (true);
}
