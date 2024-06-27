/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:26:30 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/26 18:16:52 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	- Faire en sorte que set_env cree une variable sans value dans l'environnement
	- Prendre en compte ctrl-D dans les heredocs
	- Corriger les leaks

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
		asfasf > outfile											127
		||||||||||||||||||||||||									2

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


int	loop(t_env *env, int status)
{
	t_cmd		*cmd;
	char        *input;

	cmd = NULL;
	while (1)
	{
		input = prompt(status);
		if (!input)
			return (printf("exit\n"), free_main(&cmd, &env, &input), status);
		if (check_signal(&status))
			continue;
		cmd = parsing(input, env, &status);
		if (status != 0)
			continue;
		if (input[0] != '\0')
		{
			if (check_exit(cmd, &status))
				return (free_env(&env), status);
			status = execute(cmd, env, status);
		}
		if (status == -1 || status == 255)
			return (free_main(&cmd, &env, &input), 1);
		free_final_list(&cmd);
		free(input);
	}
}

int main(int argc, char **argv, char **env)
{
	char	*new_shlvl;
	t_env	*new_env = NULL;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	new_env = init_env(env);
	if (!new_env)
		return (1);
	new_shlvl = ft_itoa(ft_atoi(get_env(&new_env, "SHLVL")) + 1);
	if (!new_shlvl)
		return (free_env(&new_env), 1);
	if (!set_env(&new_env, "SHLVL", new_shlvl))
		return (free_env(&new_env), free(new_shlvl), 1);
	free(new_shlvl);
	printf("-minishell-\n");
	loop(new_env, 0);
	return (0);
}
