/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:30:46 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/12 18:00:56 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Pour utiliser sigaction
// #define _XOPEN_SOURCE 700

# include "libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>

# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

extern int	g_signal;

/*
	Messages d'erreur
*/

# define ERROR_PIPE "syntax error near unexpected token `|'"
# define ERROR_PIPE_PIPE "syntax error near unexpected token `||'"
# define ERROR_LEFT_REDIR "syntax error near unexpected token `<'"
# define ERROR_DOUBLE_LEFT_REDIR "syntax error near unexpected token `<<'"
# define ERROR_RIGHT_REDI "syntax error near unexpected token `>'"
# define ERROR_DOUBLE_RIGHT_REDI "syntax error near unexpected token `>>'"
# define ERROR_NEWLINE "syntax error near unexpected token `newline'"
# define UNSET_NO_ARGS "unset: not enough arguments\n"

// Types d'erreurs d'execution
typedef enum	e_error_type
{
	FILE_NOT_FOUND,
	COMMAND_NOT_FOUND,
	IS_A_DIRECTORY,
	NO_SUCH_F_OR_D,
	ARGUMENT_REQUIRED,
	PERMISSION_DENIED,
	TOO_MANY_ARGS,
	NOT_VALID_ID
} e_error_type;

// Type de commande a executer
typedef enum
{
	BUILTIN,
	EXECVE,
} e_exec_type;

typedef enum
{
	T_CMD,
	T_ARG,
	T_PIPE
} token_type;

// Entree et sortie standard
typedef struct s_steams
{
	int	in;
	int	out;
} t_streams;

// Environnement sous la forme d'une liste chainee
typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
	struct s_env *prev;
} t_env;

typedef struct s_expand
{
    char			*result;
    size_t			result_size;
    char			*input;
    t_env			*env;
    size_t			pos;
    size_t			start;
} t_expand;

typedef struct s_args
{
	token_type		type;
	char			*value;
	int				quotes;//1 = single 2 = double
	struct s_args	*multi_quoted_args;
	struct s_args	*prev;
	struct s_args	*next;

}	t_args;

typedef struct s_iter_params
{
    int i;
    int start;
    bool in_quotes;
    char current_quote;
} t_iter_params;

typedef struct s_args_params
{
    t_args *args;
    t_args *last;
} t_args_params;

typedef struct s_handle_quote_params
{
    char *str;
    t_iter_params *iter;
    t_args_params *args_params;
} t_handle_quote_params;


// Entree de l'utilisateur decoupee dans une chaine delimitee par les pipes
typedef struct s_cmd
{
	char				*cmd;					// Commande à exécuter
	char				**args;					// Tableau d'arguments (y compris la commande comme premier élément), faut il enlever les redirections dans les args?
	char				**heredoc_delimiters;	// Delimiteurs pour chaque heredoc
	int					nb_heredocs;			// Nombre de heredocs dans la commande
	int					fd_heredoc;
	char 				**redir;				//"+outfile" ou "-infile"
	bool				redir_out;				// Indiquer si il y a une redir de sortie
	int					exec;					// Type d'execution builtin/execve
	
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_command
{
	char				*cmd;					// Commande à exécuter
	t_args				*args;					// Tableau d'arguments (y compris la commande comme premier élément), faut il enlever les redirections dans les args?
	char				**heredoc_delimiters;	// Delimiteurs pour chaque heredoc
	int					nb_heredocs;			// Nombre de heredocs dans la commande
	int					fd_heredoc;
	char 				**redir;				//"+outfile" ou "-infile"
	t_cmd				*final_cmd;
	
	struct s_command	*next;
}	t_command;


// int	parsing(t_command *command, char *input)

int			parsing(t_command *command, char *input, t_env *env, int status);
int			create_struct(t_command *command, char *input, t_env *env);
char		*ft_strtok_space(char *str);
char		*handle_quote_strtok(char **input, bool *in_quote, char *quote_char, char *delim);
void		*ft_realloc(void *s, size_t size);
char		*ft_strtok_pipe(char *str, char *delim);
bool		parse_and_fill_struct(t_command *command, char *segment);
int			count_args(char *input);
t_command	*init_struct(void);
void		print_string_array(char **array);
bool		add_redirection(char ***redirections, char *filename, int choice);
bool		determine_redirection_type(t_command *command, char *token, char *next_token);
bool		take_fill_redirection(t_command *command, char *token);
int			determine_quote_type(const char *token);
char		*realloc_for_more_space(char *input, char prev_char, \
bool in_single_quote, bool in_double_quote);
bool		count_when_need_space(bool in_single_quote, bool in_double_quote, char *input, int i);
char		*put_space_before_redir(char *input, int i);
bool		need_add_spaces(bool in_single_quote, bool in_double_quote, char *input, int i);
void		quote_status(bool *in_single_quote, bool *in_double_quote, char current_char);
void		determine_arg_type(char *token, t_args *new_arg, t_args *last_arg, int i);
void		add_arg_to_list(t_args *new_arg, t_args **last_arg, t_command *current);
bool		double_quote_ok(char *input);
bool		single_quote_ok(char *input);
bool		syntax_error(t_command	*command);
bool		syntax_operator_ok(t_command *command);
bool		pipe_error(t_args *current);
bool		redir_error(t_args	*current);
bool		need_add_spaces_redir(bool in_single_quote, bool in_double_quote, char *input, int i);
bool		split_for_multi_quoted(char *str, t_args *new_arg);
int			count_nodes(char *str);
bool		split_into_new_nodes(char *str, t_args *args);
t_args		*create_new_arg(const char *str, unsigned int start, size_t length);
void		add_arg_to_arg(t_args *new_arg, t_args **last_arg, t_args *current);
bool		add_redirection(char ***redirections, char *filename, int choice);
bool		add_heredoc_delimiter(t_command *command, t_args *args);
void		remove_quotes_in_delimiter(t_command *command);
bool		realloc_temp(t_command *command, int i);
void		assign_heredoc_to_arg(t_command *command);
char		*read_heredoc_content(const char *filename);
char		*heredoc(char *delimiter);
bool		heredoc_init(t_command *command);
void		*ft_realloc_string_array(void *s, size_t size);
void		process_delimiter(char *delimiter);
char		*get_env(t_env **env, char *name);
bool		strtok_name_value(char **name, char **value, int i, char **envp);
bool		malloc_set_name_value(t_env **new_node, char *name, char* value);
char		*ft_strndup(const char *s, size_t n);
void		print_command_details(t_command *command, t_env *env);
bool		init_expand(t_expand *exp, char *input, t_env *env);
char		*expand_variables(char *input, t_env *env, t_args *arg);
bool		process_variable_part(t_expand *exp, t_args *arg);
bool		process_non_variable_part(t_expand *exp);
bool		append_to_result(t_expand *exp, const char *temp);
t_command	*replace_expand(t_command *command, t_env *env);
bool		put_everything_in_final_list(t_command *command);
void		print_final_list(t_cmd *list);
void		print_final_node(t_cmd *node);
char		**ft_realloc_string_array_final(char **array, size_t new_size);
bool		add_specifier_to_struct(t_cmd **head_final_list, t_args *args, int *j);
char		*ft_unquote_result(char	*str, t_args *current);
bool		handle_multi_quoted_args(t_args	*current_multi_quoted_args, t_args *current, t_cmd *last, int *i);
void		init_new_final_list_node(t_cmd **head, t_cmd **current, t_command *command);
bool		process_unquoted_args(t_args *current, t_cmd *current_final, int *i);
bool		process_specifier_args(t_args **current, t_cmd **current_final, int *j);
bool		process_multi_quoted_args(t_args *current, t_cmd *current_final, int *i);
bool		handle_delimiter_final(t_args **current, t_cmd **current_final, int *j);
bool		process_quoted_or_unquoted(t_args *current, t_cmd *current_final, int *i);
bool		init_final_list(t_cmd **list, t_command *command);
bool		add_heredoc_to_tempfile(t_cmd *final_list);
void		print_file_content(const char *filename);
void		init_command_fields(t_command *command);
void		*ft_realloc_old_size(void *ptr, size_t old_size, size_t new_size);
int			ft_lstsize_final(t_args *lst);
bool		handle_opening_quote(t_handle_quote_params *params);
bool		handle_closing_quote(t_handle_quote_params *params);
bool		create_and_add_arg(char *str, int start, int end, t_args_params *args_params);
bool		split_into_new_nodes(char *str, t_args *args);
void		init_iter_params(t_iter_params *iter);
void		init_args_params(t_args_params *args_params, t_args *args);
void		init_handle_quote_params(t_handle_quote_params *quote_params, char *str, t_iter_params *iter, t_args_params *args_params);

// Prompt
char	*prompt(int status);
char	*get_prompt(int status);

// Execution
int		cmd_len(t_cmd *command);
bool	init_execution(pid_t **pids, t_streams *std, t_cmd *cmd, int *i);
bool	get_command(char *command, char **env, char **path);
bool	is_a_builtin(char *cmd);
bool	exec_builtin(t_cmd *command, int *status, int *pipefd, t_env *env);
int		execute(t_cmd *command, t_env *env, int status);
void	ft_execve(t_cmd *command, t_env *env);
bool	exec_execve(pid_t pid, t_cmd *command, int *pipefd, t_env *env);
bool	wait_pids(int nb_commands, pid_t *pids, int *status, int exec);

// Redirections
int		get_in(t_cmd *command);
int		get_out(t_cmd *command);
int		reset_std(int old_stdin, int old_stdout);

// Environnement
t_env	*init_env(char **envp);
bool	print_env(t_env *env);
t_env	*copy_env(t_env *env);
bool	set_env(t_env **env, char *name, char *value);
bool	unset_env(t_env **env, char *name);
char    **t_env_to_array(t_env *env);
void	free_env(t_env *env);

// Builtin commands
int		pwd(void);
void	echo(t_cmd *command);
int		cd(t_cmd *command, t_env *env);
int		export(t_cmd *command, t_env *env);

// Error
int		is_a_dir(char *cmd);
int		print_error(int type_error, char *str);

// Signals
void	sigint_handler(int sig);

#endif