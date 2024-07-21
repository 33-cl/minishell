/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:28:29 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/21 21:26:18 by maeferre         ###   ########.fr       */
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
	if (!final_env)
		return (free_final_list(&cmd), ft_free_tab(final_env), exit(status), 0);
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
		free_final_list(&cmd);
		return (free(path), ft_free_tab(final_env), exit(status), 0);
	}
	if (!((cmd->args[0][0] == ':' || cmd->args[0][0] == '!' || cmd->args[0][0]
		== '#') && !cmd->args[0][1] && !cmd->args[1]) && cmd->args[0][0])
		status = print_error(COMMAND_NOT_FOUND, cmd->args[0]);
	return (free_final_list(&cmd), ft_free_tab(final_env), exit(status), 0);
}

static bool	child_process(t_cmd *cmd, int *pipefd, t_env *env, t_process *infos)
{
	if (infos->pids)
		free(infos->pids);
	if (infos->input)
		free(infos->input);
	rl_clear_history();
	close(infos->stdin);
	close(infos->stdout);
	if (infos)
		free(infos);
	if (cmd->next != NULL && !cmd->redir_out)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (close(pipefd[1]), false);
		close(pipefd[1]);
	}
	ft_execve(cmd, env, 0);
	return (true);
}

/*
	Executes the command if it's not a builtin
	Returns a bool for function() error
*/

bool	exec_execve(t_cmd *command, int *pipefd, t_env *env, t_process *infos)
{
	command->exec = EXECVE;
	if (!ft_strrchr(command->args[0], '/')
		|| ft_strcmp(ft_strrchr(command->args[0], '/'), "/minishell"))
	{
		signal(SIGQUIT, sigquit_handler);
		signal(SIGINT, sigint_handler_child);
	}
	infos->pids[infos->nb_pids] = fork();
	if (infos->pids[infos->nb_pids] == -1)
		return (false);
	if (infos->pids[infos->nb_pids] == 0)
	{
		if (!child_process(command, pipefd, env, infos))
			return (false);
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
