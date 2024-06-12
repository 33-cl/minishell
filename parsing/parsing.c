/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:15:14 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/12 15:12:22 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// AJOUTER MON STRJOIN A LA PLACE DE CELUI DE MAEL

// qordoux@z1r2p5:~/Documents/MinishellShared/MinishellShared$ variable=valeur
// qordoux@z1r2p5:~/Documents/MinishellShared/MinishellShared$ echo "'$variable' $variable"
// 'valeur' valeur
// qordoux@z1r2p5:~/Documents/MinishellShared/MinishellShared$ echo '$variable'" $variable"
// $variable valeur
// qordoux@z1r2p5:~/Documents/MinishellShared/MinishellShared$ echo '$variable' " $variable"
// $variable  valeur
// qordoux@z1r2p5:~/Documents/MinishellShared/MinishellShared$ echo '$variable' "" " $variable"
// $variable   valeur
//quand on traite la ligne de cmd on exec d'abord le heredoc et ensuite tout le reste
// le here doc se fait pendant le parsing (expand)

/*
cmd1 "$vargument" | cmd2 argument | cmd3 'rherdoc' argument | cmd4 rinfile routfile


1. lexing separe par isspace(tab etc) et separateur
	1.1 quotes (literal / double et simple) si des simples dans des doubles, c'est le premier quote qui fait foi
2. syntaxe (erreurs)
3. expand 
	3.0 heredoc
	3.1 variables env (-> retokenisation (pour les commandes)
	3.2 trouver path -> vrmt necesaaire??
4. parsing(structure propre que je cree avec la structure initiale du lexing)
-> execution
*/
//remplacer le tableau args par une liste chainee avec un booleen pour isquote ou non ???


// J UTILISE MEMSET, RECODER LA FONCTION OU  TROUVER UNE ALTERNATIVE
//implementer $? avec une variable qui contient le code d'erreur
//ne pas prendre en compte le quoted si c'est apres un heredoc (dans un heredoc), car il met quoted en fonction du separateur 

// $H9OME n'ecris rien mais si le chiffre est apres le dollard cela recupere toute la suite genre $9HOME ou $9898876HOME8768

// MODIFS = j'ai modifie realloc et realloc string array final , ft_unquote result j'ai modif la len, 
//dans init expand j'ai ajoute un + 1 sur le malloc, j'ai modif creat new_arg pour bien initialiser, j'ai modif le + 1 dans realloc

// dans init final list je fais x3 pour que cela fonctionne cela n'est surement pas bon 

//tester : les invalide write des expand --> REGARDER APPEND_TO_RESULT

//'ok"ok'< l> o>>j>>'o' wsedrig "iuhre" weiruhg
// dans ma structure mettre une variable exit status que je met a jour 

// || -> A GERER

//aprees le dollard pas de chiffre direct, si c'est apres la premiere lettre on prend tout
// minishell> |echo -n hola
// input_copy = |e cho -n hola

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*input;
// 	t_command	*command;
// 	t_cmd		*cmd = NULL;
// 	t_env 		*env;

// 	(void)argc;
// 	(void)argv;
// 	command = NULL;
// 	env = init_env(envp);
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (input[0])
// 		{
// 			command = (t_command *)malloc(sizeof(t_command));
//    			if (!command)
//         		return (1);
// 			init_command_fields(command); 
// 			add_history(input);
// 			if (input && parsing(command, input, env, cmd) == 0)
// 			{
// 				// ft_putstr_fd("works\n", 1);
// 				print_final_list(command->final_cmd);
// 			}
// 			else
// 			{
// 				// exit(2);
// 			}
// 		}
// 		free(input);
// 	}
// 	return (0);
// }

int	parsing(t_command *command, char *input, t_env *env, int status)
{
	if (input[0] != '\0') // Pour garder le status quand on fait entree
		status = create_struct(command, input, env);
	return (status);
}

void init_command_fields(t_command *command)
{
    command->cmd = NULL;
    command->args = NULL;
    command->heredoc_delimiters = NULL;
    command->nb_heredocs = 0;
    command->fd_heredoc = -1;
    command->redir = NULL;
    command->final_cmd = NULL;
    command->next = NULL;
}

t_command	*init_struct(void)
{
	t_command	*command;
	
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	ft_memset(command, 0, sizeof(t_command));
	//faire les free au xeme appel
	//appeler une fonction qui initialise tout grace a input et sa position dans input
	return (command);
}