/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:13:57 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/26 20:22:10 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*th'is'is"a''''mess"yes"|eeeeee|"l"kl" CAUSE SEGFAULT -> regle en augmentant la taille du calloc de 1 wtf
strlen ett strjoin a prendre pour join avec mael

ok >> this < looks < working | i hopepe<please> yes
probleme avec la commande plus haute
segfault quand il y a un $ tout seul

minishell> ok << 1 | ok << 2 | ok << 3
>1
>yes
>ok
>cool
>2
>sisi
>3
Node 0:
Command: ok
Arguments: ok; ok
Heredoc Delimiters: (null)
Number of Heredocs: 0
Redirections: -|; -yes
ok
cool si rien dans heredoc il ne split pas en 3 nodes

erreur de syntaxe si rien dans un heredoc et une redir ou pipe derriere a cause du 2 eme check de syntaxe, ne pas faire le check de syntaxe si il y a un - en premier caratere
ok << 1 << 2|ok << 3 << 4 | ok << 5 | ok << 6 -->leaks*/

int	create_struct(t_command *command, char *input, t_env *env, int *status)
{
	int	result;

	result = initialize_struct(command, input, env);
	if (result != 0)
		return (result);
	return (finalize_struct(command, input, env, status));
}

int	initialize_struct(t_command *command, char *input, t_env *env)
{
	char	*input_copy;

	input_copy = ft_strdup(input);
	if (!input_copy)
		return (1);
	input_copy = put_space_before_redir(input_copy, -1);
	if (!parse_and_fill_struct(command, input_copy))
		return (free(input_copy), 1);
	free(input_copy);
	if (!syntax_error(command))
		return (2);
	if (!add_heredoc_delimiter(command, command->args))
	{	
		free_command_before(&command);
		free_env(&env);//refaire check des NULL
		free(input);
		return (1);
	}
	remove_quotes_in_delimiter(command);
	return (0);
}

int	finalize_struct(t_command *command, char *input, t_env *env, int *status)
{
	int error;

	error = 0;
	if (!heredoc_init(command))
	{
		free_command_before(&command);
		free_env(&env);
		free(input);
		return (1);
	}
	command = replace_expand(command, env, status, &error);
	if (error == 1)
		return (free_everything(command, input, env), 1);
	if (!syntax_error_after(command))
		return (2);
	if (!put_everything_in_final_list(command))
		return (1);
	add_heredoc_to_fd(command->final_cmd);
	return (0);
}

void init_heredoc(t_cmd *cmd, int *i)
{
	*i = 0;
	cmd->fd_heredoc[0] = -1;
	cmd->fd_heredoc[1] = -1;
}

bool	add_heredoc_to_fd(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;

	current = cmd;

	while (current != NULL)
	{
		if (current->redir)
		{
			init_heredoc(current, &i);
			while (current->redir[i])
			{
				if (current->redir[i][0] == '-')
				{
					if ((pipe(current->fd_heredoc)) == -1)
						return (perror("pipe"), false);
					ft_putstr_fd(current->redir[i] + 1, current->fd_heredoc[1]);
					close(current->fd_heredoc[1]);
				}
				i++;
			}
		}
		current = current->next;
	}
	return (true);
}

void	handle_quote(char c, char *last_quote, int *in_quotes, int *count)
{
	if (*in_quotes && c == *last_quote)
		*in_quotes = 0;
	else if (!*in_quotes)
	{
		*in_quotes = 1;
		*last_quote = c;
		(*count)++;
	}
}

void	check_and_increment_count(char *str, int i, char last_quote, int in_quotes, int *count)
{
	if (!in_quotes && (i == 0 || str[i - 1] == last_quote))
		(*count)++;
}

int	count_nodes(char *str)
{
	int		count;
	int		i;
	char	last_quote;
	int		in_quotes;

	count = 0;
	i = 0;
	last_quote = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			handle_quote(str[i], &last_quote, &in_quotes, &count);
		else
			check_and_increment_count(str, i, last_quote, in_quotes, &count);
		i++;
	}
	return (count);
}

t_args	*create_new_arg(const char *str, unsigned int start, size_t length)
{
	t_args *new_arg;

	new_arg = malloc(sizeof(t_args));
	if (!new_arg)
		return (NULL);
	new_arg->quotes = -1;
	new_arg->type = -1;
	new_arg->value = ft_substr(str, start, length);
	if (!new_arg->value)
	{
		free(new_arg);
		return (NULL);
	}
	new_arg->multi_quoted_args = NULL;
	new_arg->next = (NULL);
	new_arg->prev = (NULL);
	return new_arg;
}

void	init_iter_params(t_iter_params *iter)
{
	iter->i = 0;
	iter->start = 0;
	iter->in_quotes = false;
	iter->current_quote = 0;
}

void	init_args_params(t_args_params *args_params, t_args *args)
{
	args_params->args = args;
	args_params->last = NULL;
}

void	init_handle_quote_params(t_handle_quote_params *quote_params, char *str, t_iter_params *iter, t_args_params *args_params)
{
	quote_params->str = str;
	quote_params->iter = iter;
	quote_params->args_params = args_params;
}

bool	handle_opening_quote(t_handle_quote_params *params)
{
	t_args	*new_arg;

	if (params->iter->i > params->iter->start)
	{
		new_arg = create_new_arg(params->str, params->iter->start, params->iter->i - params->iter->start);
		if (new_arg == NULL)
			return (false);
		add_arg_to_arg(new_arg, &params->args_params->last, params->args_params->args);
	}
	params->iter->current_quote = params->str[params->iter->i];
	params->iter->in_quotes = true;
	params->iter->start = params->iter->i + 1;
	return (true);
}

bool	handle_closing_quote(t_handle_quote_params *params)
{
	t_args	*new_arg;

	new_arg = create_new_arg(params->str, params->iter->start, params->iter->i - params->iter->start);
	if (new_arg == NULL)
		return (false);
	if (params->iter->current_quote == '\'')
		new_arg->quotes = 1;
	else if (params->iter->current_quote == '\"')
		new_arg->quotes = 2;
	add_arg_to_arg(new_arg, &params->args_params->last, params->args_params->args);
	params->iter->in_quotes = false;
	params->iter->start = params->iter->i + 1;
	return (true);
}

bool	create_and_add_arg(char *str, int start, int end, t_args_params *args_params)
{
	t_args	*new_arg;

	new_arg = create_new_arg(str, start, end);
	if (new_arg == NULL)
		return (false);
	add_arg_to_arg(new_arg, &args_params->last, args_params->args);
	return (true);
}
bool	handle_quotes(char *str, t_handle_quote_params *quote_params, t_iter_params *iter)
{
	if (str[iter->i] == '\'' || str[iter->i] == '\"')
	{
		if (!iter->in_quotes)
		{
			if (!handle_opening_quote(quote_params))
				return (false);
		}
		else if (str[iter->i] == iter->current_quote)
		{
			if (!handle_closing_quote(quote_params))
				return (false);
		}
	}
	return (true);
}

bool	create_and_add_remaining_arg(char *str, t_iter_params *iter, t_args_params *args_params)
{
	if (iter->start < iter->i)
	{
		if (!create_and_add_arg(str, iter->start, iter->i - iter->start, args_params))
			return (false);
	}
	return (true);
}

bool	split_into_new_nodes(char *str, t_args *args)
{
	t_iter_params			iter;
	t_args_params			args_params;
	t_handle_quote_params	quote_params;

	init_iter_params(&iter);
	init_args_params(&args_params, args);
	init_handle_quote_params(&quote_params, str, &iter, &args_params);
	args->multi_quoted_args = NULL;
	while (str[iter.i])
	{
		if (!handle_quotes(str, &quote_params, &iter))
			return (false);
		iter.i++;
	}
	if (!create_and_add_remaining_arg(str, &iter, &args_params))
		return (false);

	return (true);
}

bool	split_for_multi_quoted(char *str, t_args *args)
{
	int	nb_words;

	nb_words = count_nodes(str);
	if (nb_words > 1)
		split_into_new_nodes(str, args);
	return(true);
}
t_args	*init_new_arg(char *token)
{
	t_args	*new_arg;

	new_arg = malloc(sizeof(t_args));
	if (!new_arg)
		return (NULL);
	new_arg->quotes = -1;
	new_arg->type = -1;
	new_arg->multi_quoted_args = NULL;
	new_arg->next = NULL;
	new_arg->prev = NULL;
	new_arg->value = ft_strdup(token);
	if (!new_arg->value)
	{
		free(new_arg);
		return (NULL);
	}
	return (new_arg);
}

bool	process_argument(char *token, t_command *command, t_args **last_arg, t_command *current, int i)
{
	t_args	*new_arg;

	new_arg = init_new_arg(token);
	if (!new_arg)
		return (false);
	if (ft_strcmp(new_arg->value, "<<") == 0)
		command->nb_heredocs++;
	split_for_multi_quoted(new_arg->value, new_arg);
	if (!new_arg->value)
	{
		free(new_arg);
		return (false);
	}
	determine_arg_type(token, new_arg, *last_arg, i);
	add_arg_to_list(new_arg, last_arg, current);
	return (true);
}

bool	parse_and_fill_struct(t_command *command, char *segment)
{
	char		*token;
	t_args		*last_arg;
	t_command	*current;
	int			i;

	last_arg = NULL;
	token = ft_strtok_space(segment);
	current = command;
	i = 0;
	while (token != NULL)
	{
		if (!process_argument(token, command, &last_arg, current, i))
			return (false);
		token = ft_strtok_space(NULL);
		i++;
	}
	return (true);
}

bool	realloc_temp(t_command *command, int i)
{
	char	**temp;
	size_t	new_size;
	size_t	old_size;

	old_size = sizeof(char *) * (i + 1);
	new_size = sizeof(char *) * (i + 2);
	temp = ft_realloc_old_size_bis(command->heredoc_delimiters, old_size, new_size);//check still reachable si NULL
	if (temp == NULL)
		return (false);
	command->heredoc_delimiters = temp;
	return (true);
}


void	add_arg_to_arg(t_args *new_arg, t_args **last_arg, t_args *current)
{
	if (*last_arg)
		(*last_arg)->next = new_arg;
	new_arg->prev = *last_arg;
	new_arg->next = NULL;
	if (!current->multi_quoted_args)
		current->multi_quoted_args = new_arg;
	*last_arg = new_arg;
}

void	add_arg_to_list(t_args *new_arg, t_args **last_arg, t_command *current)
{
	if (*last_arg)
		(*last_arg)->next = new_arg;
	new_arg->prev = *last_arg;
	new_arg->next = NULL;
	if (!current->args)
		current->args = new_arg;
	*last_arg = new_arg;
}

void	determine_arg_type(char *token, t_args *new_arg, t_args *last_arg, int i)
{
	// new_arg->quotes = 0;
	new_arg->quotes = determine_quote_type(token);
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "\'|\'") == 0 || ft_strcmp(token, "\"|\"") == 0)//ne gere pas si il y a plusieurs espaces, gerer ailleurs son type
		new_arg->type = T_PIPE;
	else if (ft_strcmp(token, "<<") == 0)
		new_arg->type = T_HEREDOC;
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">>") == 0)
		new_arg->type = T_REDIR;
	else if (i == 0)
		new_arg->type = T_CMD;
	else
		new_arg->type = T_ARG;
	new_arg->prev = last_arg;
	new_arg->next = NULL;
}

int	determine_quote_type(const char *token)
{
	bool	in_single_quote;
	bool	in_double_quote;
	bool	is_escaped;

	in_single_quote = false;
	in_double_quote = false;
	is_escaped = false;
	while (*token)
	{
		if (is_escaped)
			is_escaped = false;
		else if (*token == '\\')
			is_escaped = true;
		else if (*token == '\'' && !in_double_quote && !in_single_quote && !is_escaped)
			in_single_quote = !in_single_quote;
		else if (*token == '\"' && !in_single_quote && !in_double_quote && !is_escaped)
			in_double_quote = !in_double_quote;
		token++;
	}
	if (in_single_quote)
		return (1);
	else if (in_double_quote)
		return (2);
	else
		return (0);
}
