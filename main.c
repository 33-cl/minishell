/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:26:30 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:47 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	- Probleme de init_execution au lancement sans l'environnement
*/

#include "minishell.h"

int	loop(t_env *env, t_cmd *cmd, int status, int old_status)
{
	char	*input;

	input = NULL;
	while (1)
	{
		if (handle_signals_n_reset(&status, &input, &old_status))
			continue ;
		if (check_signal(&status) || !prompt(&status, &input))
			continue ;
		if (!input || status == -1)
			return (printf("exit\n"), rl_clear_history(),
				free_main(&cmd, &env, &input), status);
		cmd = parsing(input, env, &status, &old_status);
		if (status == 1)
			return (free_main(&cmd, &env, &input), 1);
		if (status == 2)
			continue ;
		if (input && input[0] != '\0' && check_exit(cmd, &old_status))
			return (free_final_list(&cmd), rl_clear_history(), free_env(&env),
				free(input), input = NULL, old_status);
		else if (input[0] != '\0')
			status = execute(cmd, env, status, &input);
		if (free_final_list(&cmd), status == -1 || status == 255)
			return (free_main(&cmd, &env, &input), 1);
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
	if (return_value == -1 || return_value == 255)
		return (1);
	return (return_value);
}
