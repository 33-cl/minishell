/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:26:30 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/19 23:01:51 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	- Probleme de init_execution au lancement sans l'environnement
	- Creer la chaine cmd dans le cas ou on met entree en commentaire pour ne pas segfault
*/

#include "minishell.h"

int	loop(t_env *env, t_cmd *cmd, int status, int old_status)
{
	char	*input;
	char	*pwd;

	cmd = NULL;
	(void)pwd;
	while (1)
	{	
		if (handle_signals(&status))
			continue ;
		input = prompt(&status);
		if (check_signal(&status))
			continue ;
		if (!input)
			return (printf("exit\n"), rl_clear_history(),
				free_main(&cmd, &env, &input), status);
		cmd = parsing(input, env, &status, &old_status);
		if (status == 1)
			return (free_main(&cmd, &env, &input), 1);
		if (status == 2)
			continue ;
		if (input && input[0] != '\0' && check_exit(cmd, &old_status))
			return (free_final_list(&cmd), rl_clear_history(), free_env(&env),
				free(input), old_status);
		else if (input[0] != '\0')
			status = execute(cmd, env, status, &input);
		if (free_final_list(&cmd), status == -1 || status == 255)
			return (free_main(&cmd, &env, &input), 1);
		if (input)
			free(input);
		old_status = status;
	}
}

int	main(int argc, char **argv, char **env)
{
	int		return_value;
	char	*new_shlvl;
	t_env	*new_env;

	(void)argc;
	(void)argv;
	new_env = NULL;
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
	if (!skip_first_rl())
		return (1);
	return_value = loop(new_env, NULL, 0, 0);
	return (return_value);
}
