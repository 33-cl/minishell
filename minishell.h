/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:30:46 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/29 13:48:24 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>

# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

typedef struct  s_redirection
{
	// Permet d'avoir les redirections dans l'ordre avec 1 ou 2 devant pour indiquer 
	// si il s'agit d'un >>/<< ou >/<

	// Exemple : << eof < infile << test cat >> outfile > out > file2
	char    **in;  // {"2eof", "1infile", "2test"}
	char    **out; // {"2outfile", "1out", "1file2"}
} t_redirection;

typedef struct  s_command
{
	char                *cmd;           // "ls -l"	(sans les redirections)
	char                **args;         // {"ls", "-l"}
	t_redirection       redir;
	struct s_command    *next;
	int					status;
} t_command;


char	*prompt(int status);
char	*get_path(char *command, char **env);
int     execute(t_command *command, char **env);

// Builtin commands
int		pwd(void);
void    echo(t_command *command);
int		cd(t_command *command);

#endif