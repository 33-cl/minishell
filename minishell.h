/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:30:46 by maeferre          #+#    #+#             */
/*   Updated: 2024/04/20 00:14:39 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	char                *cmd;           // "ls -l"
    char                **args;         // {"ls", "-l"}
    char                **redirections; // {"< infile", ">> outfile"}
    int                 nb_heredocs;
    char                **heredoc_delimiters;
    struct s_command    *next;
} t_command;


char	*prompt(int status);
char	*get_path(char *command, char **env);
int     execute(t_command *command, char **env, int status);

// Builtin commands
int		pwd(void);
void    echo(t_command *command);
int		cd(t_command *command);

#endif