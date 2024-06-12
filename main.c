/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:26:30 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/12 18:08:11 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	- return status pour get_command (tester avec casser malloc ft_split)
	- Refaire les signaux avec sigaction
	- Faire les heredocs avec des pipes
	- Proteger pwd en cas de fail
	- Modifier set_env pour le creer sans value
	- Gere le programme   sans env / sans PATH / sans SHLVL etc.
	- Probleme quand minishell dans minishell
	- Une fonction qui free tout le programme quand on l'appelle

	ERREURS

	comportement
		ls | cat | cat >> out										0
		ls > out | grep o											1
		ls | cat > out | < Makefile grep o							0
		ls -l >out | ls												0
		< Makefile | ls												0
		cat | cat | ls												0
		chmod 000 infile ; cat <infile								1
		chmod 000 out ; ls >out										1
		unset SHLVL ; ./minishell
		echo hello world > out | ls > out2							0
		echo salut | khiuashdf > salut | echo au revoir				0
		chmod 000 outfile ; asfasf > outfile						1

	Premiere commande
		IN  : redir / standard
		OUT : redir / pipe / standard

	Commandes du millieu
		IN  : redir / pipe
		OUT : redir / pipe

	Derniere commande
		IN  : redir / pipe
		OUT : redir / standard

*/



int	loop(t_env *env)
{
	t_command   *command;
	t_cmd		*cmd;
	char        *input;
	int			status;

	command = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (1);
	status = 0;
	while (1)
	{
		if (status == 255)
			return (1);

		// Init quentin
		init_command_fields(command);

		// Prompt
		input = prompt(status);
		if (!input || !ft_strcmp(input, "exit"))
			return (printf("exit\n"), status); // + free tout

		// Check des signaux recus
		if (g_signal == 1)
		{
			status = 130;
			g_signal = 0;
			continue ;
		}

		// Parsing
		status = parsing(command, input, env, status);
		if (status != 0)
			continue;
		cmd = command->final_cmd;

		// print_final_list(cmd);

		// Execution
		if (input[0] != '\0')
			status = execute(cmd, env, status);
		if (status == -1)
			return (status);
	}
	return (status);
}

int main(int argc, char **argv, char **env)
{
	int		status;
	t_env	*new_env; 

	(void)argc;
	(void)argv;
	status = 0;

	// Gestion des signaux
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	// Convertion de l'environnement
	new_env = init_env(env);
	set_env(&new_env, "SHLVL", ft_itoa(ft_atoi(get_env(&new_env, "SHLVL")) + 1)); // Incrementer SHLVL dans env

	printf("-minishell-\n");
	status = loop(new_env);

	return (status);
}
