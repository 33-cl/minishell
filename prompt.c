/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:51:41 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/30 18:11:25 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Cree et affiche la ligne de l'invite de commande qui est affichee
	par readline

	On cherche le path actuel avec getcwd
	/home/maeferre/Desktop/minishell
	
	Puis on garde uniquement le dernier dossier grace a strrchr
	minishell
*/

static char	*get_prompt(int status);


char	*prompt(int status)
{
	char	*prompt;
	char	*input;

	prompt = get_prompt(status);
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	add_history(input);
	free(prompt);
	return (input);
}


static char	*get_prompt(int status)
{
	char	*command;
	char	*cwd;

	// Icone a gauche du prompt qui change de couleur on fonction du status
	if (status == 0)
		command = ft_strdup("\033[0;32m♦ \033[1;35m");	
	else
		command = ft_strdup("\033[0;31m♦ \033[1;35m");
	if (!command)
		return (NULL);

	// Cherche le chemin actuel puis garde uniquement le nom du dernier dossier
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(command), NULL);
	cwd = ft_strdup(ft_strrchr(cwd, '/') + 1);
	if (!cwd)
		return (free(command), NULL);
	command = ft_strjoin(command, cwd);
	if (!command)
		return (NULL);
	free(cwd);
	
	// Pour Reinitialiser les couleurs
	command = ft_strjoin(command, " \033[0m");
	if (!command)
		return (NULL);

    return (command);
}
