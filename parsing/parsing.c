/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:15:14 by qordoux           #+#    #+#             */
/*   Updated: 2024/07/09 02:28:38 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
j'ai un \n si je ctrl c dans un heredoc alors qu il ne faut pas

ok >> this < looks < working | i hopepe<please> yes -> 
pas le meme message que bash, est-ce qu on affiche les erreur apres le pipe,
est-ce qu'on peut afficher 2 messages d'erreur a la suite

ok > $HOME < $PATH > $YES > OUI < NON | OUI -> on ne s'arrete pas a la
premiere erreur mais on affiche l'erreur du path + mon affiche pas 
l'erreur de oui 

voir le bail de si erreur de syntaxe dans une var

1. lexing separe par isspace(tab etc) et separateur
	1.1 quotes (literal / double et simple) si des simples 
	dans des doubles, c'est le premier quote qui fait foi
2. syntaxe (erreurs)
3. expand 
	3.0 heredoc
	3.1 variables env (-> retokenisation (pour les commandes)
	3.2 trouver path
4. parsing(structure propre que je cree avec la structure 
initiale du lexing)
-> execution

$9898876HOME8768 -> pas le bon message

commentaires a virer
expand->utils
free_utils(voir quand j'aurais retest les malloc a NULL)
heredoc/readline_until_delimiter(voir apres check NULL)

*/

t_cmd	*parsing(char *input, t_env *env, int *status)
{
	t_command	*command;
	t_cmd		*final_cmd;

	command = NULL;
	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
	{
		*status = -1;
		return (NULL);
	}
	init_command_fields(command);
	if (input[0] != '\0')
		*status = create_struct(command, input, env, status);
	final_cmd = command->final_cmd;
	free_command(&command);
	return (final_cmd);
}
