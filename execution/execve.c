/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:28:29 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/12 17:59:14 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Execute la commande lorsqu'on connait l'entree et la sortie de la commande

	(Au check du status d'erreur, attention a EXIT_SUCCESS a la fin de chaque builtin)
*/

void	ft_execve(t_cmd *cmd, t_env *env)
{
	int		status;
	char	*path;
	char	**final_env;
	
	status = 0;
	final_env = t_env_to_array(env);
	if (!final_env)
		exit(-1);
	if (!get_command(cmd->args[0], final_env, &path))
		exit(-1);
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
		free(path);
		ft_free_tab(final_env);
		exit(status);
	}
	if (!((cmd->args[0][0] == ':' || cmd->args[0][0] == '!') 
		&& !cmd->args[0][1] && !cmd->args[1]) && cmd->args[0][0])
		status = print_error(COMMAND_NOT_FOUND, cmd->args[0]);
	ft_free_tab(final_env);
	exit(status);
}

/*
	Execute la commande dans le cas ou il faut l'executer avec execve
	Renvoie un booleen indiquant en cas d'erreur de fonctions
*/

bool	exec_execve(pid_t pid, t_cmd *command, int *pipefd, t_env *env)
{
	command->exec = EXECVE;
	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		if (command->next != NULL && !command->redir_out)
		{
			close(pipefd[0]);
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				return (close(pipefd[1]), false);
			close(pipefd[1]);
		}
		ft_execve(command, env);
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
