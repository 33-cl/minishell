/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:51:41 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/03 17:20:14 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Cree et affiche la ligne de l'invite de commande qui est affichee
	par readline

	On cherche le path actuel avec getcwd
	/home/maeferre/Desktop/minishell
	
	Puis on garde uniquement le dernier dossier grace a strrchr
	minishell
*/

char	*prompt(int status)
{
	char	*prompt;
	char	*input;

	prompt = get_prompt(status);
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	if (input == NULL)
		return (free(prompt), NULL);
	add_history(input);
	free(prompt);
	return (input);
}

char	*get_prompt(int status)
{
	char	*command;
	char	*cwd;
	char	*final_cwd;

	if (status == 0)
		command = ft_strdup("\033[0;32m♦ \033[1;35m");
	else
		command = ft_strdup("\033[0;31m♦ \033[1;35m");
	if (!command)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(command), NULL);
	final_cwd = ft_strdup(ft_strrchr(cwd, '/') + 1);
	free(cwd);
	if (!final_cwd)
		return (free(command), NULL);
	command = ft_strjoin_free(command, final_cwd, 3);
	if (!command)
		return (NULL);
	command = ft_strjoin_free(command, " \033[0m", 1);
	if (!command)
		return (NULL);
	return (command);
}
