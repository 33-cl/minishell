/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:13:57 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/12 15:12:14 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// th'is'is"a''''mess"yes"|eeeeee|"l"kl" CAUSE SEGFAULT -> regle en augmentant la taille du calloc de 1 wtf
// strlen ett strjoin a prendre pour join avec mael

//ok >> this < looks < working | i hopepe<please> yes
//probleme avec la commande plus haute

int	create_struct(t_command *command, char *input, t_env *env)
{
	char		*input_copy;
	// t_env		*env;

	// (void)env;
	// (void)envp;
	input_copy = ft_strdup(input);
	input_copy = put_space_before_redir(input_copy, -1);
	if (!input_copy)
		return (1);
	parse_and_fill_struct(command, input_copy);
	free(input_copy);
	if (!syntax_error(command))
		return (2);
	if (!add_heredoc_delimiter(command, command->args))
		return (1);
	remove_quotes_in_delimiter(command);
	heredoc_init(command);
	// env = init_env(envp);
	command = replace_expand(command, env);
	// print_command_details(command, env);
	put_everything_in_final_list(command);
	return (0);
}

int count_nodes(char *str)//norminette
{
	int count = 0;
	int i = 0;
	char last_quote = 0;
	int in_quotes = 0;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quotes && str[i] == last_quote)
				in_quotes = 0;
			else if (!in_quotes)
			{
				in_quotes = 1;
				last_quote = str[i];
				count++; // Chaque début de guillemets compte comme un nouveau mot
			}
		}
		else if (!in_quotes && (i == 0 || str[i-1] == last_quote))
			count++;
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

// bool	split_into_new_nodes(char *str, t_args *args)
// {
// 	int		i;
// 	int		start;
// 	t_args	*last;
// 	t_args	*new_arg;
// 	char	current_quote;
// 	bool	in_quotes;

// 	i = 0;
// 	start= 0;
// 	last = NULL;
// 	in_quotes = false;
// 	current_quote = 0;
// 	args->multi_quoted_args = NULL;

// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')
// 		{
// 			if (!in_quotes)
// 			{
// 				if (i > start)
// 				{
// 					new_arg = create_new_arg(str, start, i - start);
// 					if (new_arg == NULL)
// 						return (false);
// 					add_arg_to_arg(new_arg, &last, args);
// 				}
// 				current_quote = str[i];
// 				in_quotes = true;
// 				start = i + 1;
// 			}
// 			else if (str[i] == current_quote)
// 			{
// 				new_arg = create_new_arg(str, start, i - start);
// 				if (!new_arg)
// 					return (false);
// 				if (current_quote == '\'')
// 					new_arg->quotes = 1;
// 				else if (current_quote == '\"')
// 					new_arg->quotes = 2;
// 				add_arg_to_arg(new_arg, &last, args);
// 				in_quotes = false;
// 				start = i + 1;
// 			}
// 		}
// 		i++;	
// 	}
// 	if (start < i)
// 	{
// 		new_arg = create_new_arg(str, start, i - start);
// 		if (!new_arg)
// 			return(false);
// 		add_arg_to_arg(new_arg, &last, args);
// 	}
// 	return (true);
// }

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
		if (str[iter.i] == '\'' || str[iter.i] == '\"')
		{
			if (!iter.in_quotes)
			{
				if (!handle_opening_quote(&quote_params))
					return (false);
			}
			else if (str[iter.i] == iter.current_quote)
			{
				if (!handle_closing_quote(&quote_params))
					return (false);
			}
		}
		iter.i++;
	}
	if (iter.start < iter.i)
	{
		if (!create_and_add_arg(str, iter.start, iter.i - iter.start, &args_params))
			return (false);
	}
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
//pour heredoc appel a readline et je join a chaques fois le resultat dans la meme ligne 

bool	parse_and_fill_struct(t_command *command, char *segment)
{
	char		*token;
	t_args		*new_arg;
	t_args		*last_arg;
	t_command	*current;
	int			i;

	last_arg = NULL;
	token = ft_strtok_space(segment);
	current = command;
	i = 0;
	while(token != NULL)
	{
		new_arg = malloc(sizeof(t_args));
		if (!new_arg)
			return (false);
		ft_memset(new_arg, 0, sizeof(t_args));
		new_arg->value = ft_strdup(token);
		if (ft_strcmp(new_arg->value, "<<") == 0)
			command->nb_heredocs++;
		split_for_multi_quoted(new_arg->value, new_arg);
		if (!new_arg->value)
			return (false);
		determine_arg_type(token, new_arg, last_arg, i);
		add_arg_to_list(new_arg, &last_arg, current);
		token = ft_strtok_space(NULL);
		i++;
	}
	return (true);
}

bool	realloc_temp(t_command *command, int i)
{
	char	**temp;

	temp = ft_realloc_string_array(command->heredoc_delimiters, sizeof(char *) * (i + 2));
	if (temp == NULL)
	{
		free(command->heredoc_delimiters);
		return (false);
	}
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
