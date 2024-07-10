/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:21:46 by qordoux           #+#    #+#             */
/*   Updated: 2024/07/07 15:03:14 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*si le delimiter heredoc est entre double guillemets j'expand il ne faut pas 
si j'ai le delimiter entre quote je n'expand pas mais moi je vire le dollard 
alors que je devrais le garder
ok > $yes < ok > $yes < $yes < $HOME > $yes
probleme ici je print 2x home

faire les free de clear history

est-ce que j'ai toujpours besoin de free argument?
void	free_argument(t_args *arg)
{
	if (arg->value)
		free(arg->value);
	// free(arg);
} */

bool	init_expand(t_expand *exp, char *input, t_env *env)
{
	exp->input = input;
	exp->env = env;
	exp->result_size = ft_strlen(input) + 1;
	exp->result = malloc(sizeof(char) * exp->result_size + 1);
	if (exp->result == NULL)
		return (false);
	exp->result[0] = '\0';
	exp->pos = 0;
	exp->start = 0;
	return (true);
}

char	*handle_dollar_sign(char *input, t_args *arg)
{
	if ((ft_strcmp(input, "$") == 0 && !arg->next))
		return (ft_strdup("$"));
	if (ft_strcmp(input, "$") == 0 && (arg->quotes == 0 || arg->quotes == -1) \
	&& arg->next && (arg->next->quotes == 2 || arg->next->quotes == 1))
		return (ft_strdup(input + 1));
	return (NULL);
}

t_args	*remove_empty_argument(t_command *command, t_args *arg)
{
	t_args	*next_arg;

	next_arg = arg->next;
	if (arg->prev != NULL)
		arg->prev->next = arg->next;
	if (arg->next != NULL)
		arg->next->prev = arg->prev;
	if (arg == command->args)
		command->args = arg->next;
	free(arg->value);
	return (next_arg);
}
/*est-ce que je ne dois pas free arg aussi?, cela semble causer des 
problemes ailleurs*/

void	handle_expanded_value(t_command *command, t_args *arg, char *expanded, \
int *error)
{
	if (expanded == NULL)
	{
		*error = 1;
		return ;
	}
	if ((ft_strcmp(expanded, "") == 0 && arg == command->args) || \
	(ft_strcmp(expanded, "") == 0 && arg->prev && arg->prev->type != 3 && \
	arg->prev->type != 4))
		arg = remove_empty_argument(command, arg);
	else
	{
		free(arg->value);
		arg->value = expanded;
	}
}
