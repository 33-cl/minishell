/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:30:46 by maeferre          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:19 by maeferre         ###   ########.fr       */
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
# include <signal.h>

# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

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
# define FAR ": filename argument required\n.: usage: . filename [arguments]\n"
# define CWD_DELETED "error : current working directory has been deleted\n"

typedef enum e_signal
{
	NO_SIGNAL,
	INT,
	INT_C,
	QUIT
}	t_signal;

typedef enum e_error_type
{
	FILE_NOT_FOUND,
	COMMAND_NOT_FOUND,
	IS_A_DIRECTORY,
	NO_SUCH_F_OR_D,
	ARGUMENT_REQUIRED,
	PERMISSION_DENIED,
	TOO_MANY_ARGS,
	NOT_VALID_ID,
	NOT_SET
}	t_error_type;

typedef enum e_exec_type
{
	NONE,
	BUILTIN,
	EXECVE,
}	t_exec_type;

typedef enum e_token_type
{
	T_CMD,
	T_ARG,
	T_PIPE,
	T_REDIR,
	T_HEREDOC
}	t_token_type;

typedef struct s_space_insertion_params
{
	int		i;
	int		len;
	bool	in_single_quote;
	bool	in_double_quote;
}	t_space_insertion_params;

typedef struct s_expand
{
	char			*result;
	size_t			result_size;
	char			*input;
	struct s_env	*env;
	size_t			pos;
	size_t			start;
}	t_expand;

typedef struct s_env
{
	char			*name;
	char			*value;
	t_expand		exp_result;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_process
{
	int		stdin;
	int		stdout;
	pid_t	*pids;
	int		nb_pids;
	char	*input;
	int		piped;
	t_env	*env;
}	t_process;

typedef struct s_args
{
	int				type;
	char			*value;
	int				quotes;
	struct s_args	*multi_quoted_args;
	struct s_args	*prev;
	struct s_args	*next;
}	t_args;

typedef struct s_iter_params
{
	int		i;
	int		start;
	bool	in_quotes;
	char	current_quote;
}	t_iter_params;

typedef struct s_args_params
{
	t_args	*args;
	t_args	*last;
}	t_args_params;

typedef struct s_handle_quote_params
{
	char			*str;
	t_iter_params	*iter;
	t_args_params	*args_params;
}	t_handle_quote_params;

typedef struct s_cmd
{
	char				*cmd;
	char				**args;
	char				**heredoc_delimiters;
	int					nb_heredocs;
	int					fd_heredoc[2];
	bool				malloc_failed;
	char				**redir;
	bool				redir_out;
	int					exec;
	int					last_exec;
	int					i;
	int					j;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}	t_cmd;

typedef struct s_command
{
	char				*cmd;
	t_args				*args;
	char				**heredoc_delimiters;
	int					nb_heredocs;
	int					fd_heredoc;
	char				**redir;
	int					malloc_error;
	t_cmd				*final_cmd;
	int					index;
	struct s_command	*next;
}	t_command;

// Parsing
t_cmd		*parsing(char *input, t_env *env, int *status, int *old_status);
char		*ft_strtok_space(char *str);
char		*handle_quote_strtok(char **input, bool *in_quote, \
char *quote_char, char *delim);
int			create_struct(t_command *command, char *input, \
t_env *env, int *status);
bool		parse_and_fill_struct(t_command *command, char *segment);
void		print_string_array(char **array);
int			determine_quote_type(const char *token);
char		*realloc_for_more_space(char *input, \
bool in_single_quote, bool in_double_quote);
char		*put_space_before_redir(char *input, int i);
bool		need_add_spaces(bool in_single_quote, bool in_double_quote, \
char *input, int i);
void		quote_status(bool *in_single_quote, bool *in_double_quote, \
char current_char);
void		determine_arg_type(char *token, t_args *new_arg, \
t_args *last_arg, int i);
void		add_arg_to_list(t_args *new_arg, t_args **last_arg, \
t_command *current);
bool		double_quote_ok(char *input);
bool		single_quote_ok(char *input);
bool		syntax_error(t_command	*command);
bool		syntax_operator_ok(t_command *command);
bool		pipe_error(t_args *current);
bool		redir_error(t_args	*current);
bool		need_add_spaces_redir(bool in_single_quote, bool in_double_quote, \
char *input, int i);
t_args		*create_new_arg(const char *str, unsigned int start, size_t length);
void		add_arg_to_arg(t_args *new_arg, t_args **last_arg, t_args *current);
bool		add_heredoc_delimiter(t_command *command, t_args *args);
void		remove_quotes_in_delimiter(t_command *command);
bool		realloc_temp(t_command *command, int i);
bool		heredoc_init(t_command *command, int *error);
void		process_delimiter(char *delimiter);
char		*get_env(t_env **env, char *name);
bool		strtok_name_value(char **name, char **value, int i, char **envp);
char		*ft_strndup(const char *s, size_t n);
bool		init_expand(t_expand *exp, char *input, t_env *env);
bool		process_variable_part(t_expand *exp, t_args *arg, int *status);
bool		process_non_variable_part(t_expand *exp);
t_command	*replace_expand(t_command *command, t_env *env, int *status, \
int *error);
bool		put_everything_in_final_list(t_command *command);
void		print_final_list(t_cmd *list);
char		**ft_realloc_string_array_final(char **array, size_t new_size);
bool		add_specifier_to_struct(t_cmd **head_final_list, t_args *args, \
int *j);
bool		handle_multi_quoted_args(t_args	*current_multi_quoted_args, \
t_cmd *last, int *i);
bool		init_new_final_list_node(t_cmd **head, t_cmd **current, \
t_command *command);
int			process_quoted_or_unquoted(t_args *current, t_cmd *current_final, \
int *i);
void		init_command_fields(t_command *command);
void		*ft_realloc_old_size(void *ptr, size_t old_size, \
size_t new_size);
int			ft_lstsize_final(t_args *lst);
void		init_iter_params(t_iter_params *iter);
void		init_args_params(t_args_params *args_params, t_args *args);
void		init_handle_quote_params(t_handle_quote_params *quote_params, \
char *str, t_iter_params *iter, t_args_params *args_params);
void		free_command(t_command **command);
void		free_args(t_args **args);
void		free_final_list(t_cmd **final_cmd);
char		*remove_dollar_sign(char *str);
bool		add_heredoc_to_fd(t_cmd *cmd);
bool		syntax_operator_after(t_command *command);
bool		syntax_error_after(t_command	*command);
bool		redir_error_after(t_args	*current);
bool		pipe_error_after(t_args *current);
char		**ft_realloc_string_array_final_bis(char **array, \
size_t new_size);
void		*ft_realloc_old_size_bis(void *ptr, size_t old_size, \
size_t new_size);
int			finalize_struct(t_command *command, t_env *env, \
int *status);
int			initialize_struct(t_command *command, char *input);
char		*realloc_and_init(char *input, bool *in_single_quote, \
bool *in_double_quote);
void		free_resources(char *name, char *value, t_env **current);
void		initialize_vars(int *i, t_env **current, char **name, \
char **value);
void		free_final_list_bis(t_cmd **final_cmd);
bool		handle_quotes(char *str, t_handle_quote_params *quote_params, \
t_iter_params *iter);
bool		create_and_add_remaining_arg(char *str, t_iter_params *iter, \
t_args_params *args_params);
t_args		*init_new_arg(char *token);
void		handle_quote(char c, char *last_quote, int *in_quotes, int *count);
char		*read_line_until_delimiter(char *delimiter, int len, int *error);
char		*handle_dollar_sign(char *input, t_args *arg);
char		*expand_argument_value(t_args *arg, t_env *env, int *status);
bool		handle_expanded_value(t_command *command, t_args *arg, \
char *expanded, int *error);
void		expand_multi_quoted_args(t_args *arg, t_env *env, int *status);
int			handle_current_element(t_args **current, t_cmd **current_final);
bool		process_current(t_args *current, t_cmd *current_final, \
t_command *command);
bool		handle_new_final_node(t_cmd **head_final_list, \
t_cmd **current_final, t_command *command);
int			duplicate_cmd(t_args *current, t_cmd *current_final);
int			realloc_args_array(t_args *current, t_cmd *current_final);
bool		handle_tmp3_processing(char *tmp2, t_args *current, \
t_cmd **head_final_list, int *j);
bool		handle_tmp2_processing(char *tmp, t_args *current, \
t_cmd **head_final_list, char **tmp2);
void		process_redirection_heredoc(char *str, t_args *current, \
t_cmd **head_final_list, int *j);
char		*concatenate_strings(const char *s1, const char *s2);
void		free_two_strings(char *s1, char *s2);
void		free_single_cmd(t_cmd *cmd);
void		print_command(char *cmd);
void		print_arguments(char **args);
void		print_heredoc_delimiters(char **heredoc_delimiters);
void		print_redirections(char **redir);
int			process_quoted_arg(t_args *current, t_cmd *current_final, int *i);
int			process_unquoted_arg(t_args *current, t_cmd *current_final, int *i);
void		free_command_before(t_command **command);
void		free_heredoc_delimiters(char **heredoc_delimiters);
char		*expand_argument_value_multi(t_args *arg, t_env *env, int *status);
bool		append_to_result_itoa(t_expand *exp, char *temp);

// Prompt
int			prompt(int *status, char **input);
char		*get_prompt(int *status);
bool		skip_first_rl(void);

// Execution
int			cmd_len(t_cmd *command);
t_process	*init_execution(t_process *infos, t_cmd *cmd, char **input,
				t_env *env);
bool		check_exit(t_cmd *command, int *status);
int			get_command(char *command, char **env, char **path);
bool		is_a_builtin(char *cmd);
bool		exec_builtin(t_cmd *command, int *status, int *pipefd, t_env *env);
int			execute(t_cmd *command, t_env *env, int status, char **input);
int			ft_execve(t_cmd *command, t_env *env, int status);
bool		exec_execve(t_cmd *command, int *pipefd, t_env *env,
				t_process *infos);
void		wait_pids(t_process *infos, int *status, int exec);

// Redirections
int			get_in(t_cmd *command, size_t i, int fd);
int			get_out(t_cmd *command, size_t i, int fd);
bool		reset_std(t_process *infos);
bool		reset_stdin(t_cmd *cmd, t_process *infos);

// Environnement
t_env		*init_env(char **envp);
t_env		*reverse_env(t_env *env);
bool		print_env(t_env *env);
bool		print_env_reverse(t_env *env);
t_env		*copy_env(t_env *env);
bool		set_env(t_env **env, char *name, char *value);
bool		set_env_export(t_env **env, char *name, char *value);
bool		unset_env(t_env **env, char *name);
char		**t_env_to_array(t_env *env);
void		free_env(t_env **env);

// Builtin commands
int			pwd(t_cmd *command);
void		echo(t_cmd *command);
int			cd(t_cmd *command, t_env *env);
int			export(t_cmd *command, t_env *env);
int			unset(t_env **env, char **args);

// Free
void		free_main(t_cmd **cmd, t_env **env, char **input);
void		freee(t_cmd **final_cmd);
void		free_main_no_free_input(t_env **env);

// Errors
int			is_a_dir(char *cmd);
int			print_error(int type_error, char *str);

// Signals
bool		handle_signals_n_reset(int *status, char **input, int *old_status);
bool		check_signal(int *status);
void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		sigint_handler_child(int sig);
void		sigint_handler_heredoc(int sig);

#endif