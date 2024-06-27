/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_or_not_final.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qordoux <qordoux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:09:46 by qordoux           #+#    #+#             */
/*   Updated: 2024/06/25 17:02:48 by qordoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//stocker le dernier heredoc dans un fichier avec putstr_fd et stocker son fd 

// ATTENTION si multi quoted, je vire pas les quotes pour les delimiter

//modifier set_env pour que cela ajoute une variable d'environnement vide si je lui donne une value nulle

int	process_quoted_or_unquoted(t_args *current, t_cmd *current_final, int *i)
{

	if ((!current->prev && current->type != 3) || (current->prev && current->prev->type != 3))
	{
		if (current->multi_quoted_args)
			{
				if (!(process_multi_quoted_args(current, current_final, &(*i))))
					return (2);
			}
			else
			{
				//continuer leaks
				if (process_unquoted_args(current, current_final, &(*i)) == 2)
					return (2);
			}
	}
	return (0);
}

bool	process_multi_quoted_args(t_args *current, t_cmd *current_final, int *i)
{
    t_args	*current_multi_quoted_args;

	current_multi_quoted_args = current->multi_quoted_args;
    if (!handle_multi_quoted_args(current_multi_quoted_args, current, current_final, i))
		return (false);
	return (true);
}

int	process_unquoted_args(t_args *current, t_cmd *current_final, int *i)
{
    char	*unquoted_result;
	int		len;

	if (current->type == 0)
	{
		if (current_final->cmd)
			free(current_final->cmd);
		current_final->cmd = ft_strdup(current->value);
		if (current_final->cmd == NULL)
			return (2);//est-ce que cela ne pose pas de probleme?
	}
	len = ft_lstsize_final(current);
    current_final->args = ft_realloc_string_array_final_bis(current_final->args, len + 1);
    if (current_final->args == NULL)
	{
		return (2);
	}
	if (current->quotes != 0 && (current->prev == NULL || ft_strcmp(current->prev->value, "<<") != 0))
	{
        unquoted_result = ft_unquote_result(current->value, current);
		if(unquoted_result == NULL)
			return (2);
        current_final->args[*i] = ft_strdup(unquoted_result);
		if(current_final->args[*i] == NULL)
		{
			free(unquoted_result);
			return (2);
		}
		free(unquoted_result);
	}
    else
	{
		if (current_final->cmd)
		{
			free(current_final->cmd);
			current_final->cmd = NULL;
		}
		//continuer leaks ici
        current_final->args[*i] = ft_strdup(current->value);
		if (current_final->args[*i] == NULL)
			return (2);
		current_final->cmd = ft_strdup(current_final->args[0]);//ici probleme
		if (current_final->cmd == NULL)
			return (2);
	}
    (*i)++;
	// current_final->args[*i] = NULL;
	return (0);
}

//retoucher la fonction du dessous, plus besoin de current

bool	handle_multi_quoted_args(t_args	*current_multi_quoted_args, t_args *current, t_cmd *current_final, int *i)
{
	char	*new_str;
	char	*temp;
	char	*new_temp;

	(void)current;//ici delete
	temp = ft_strdup("");
	if (temp == NULL)
		return (false);
	while (current_multi_quoted_args != NULL)
	{
		// if (current->type == 0)
		// 	current_final->cmd = ft_strdup(current->multi_quoted_args->value);//cela
		new_str = ft_strdup(current_multi_quoted_args->value);
		if (new_str == NULL)
		{
			free(temp);
			return (false);
		}
		new_temp = ft_strjoin(temp, new_str);
		if (new_temp == NULL)
		{
			free(temp);
			free(new_str);
			return (false);
		}
		free(temp);
		temp = new_temp;
		free(new_str);
		current_multi_quoted_args = current_multi_quoted_args->next;
	}
	current_final->args[*i] = temp;
	(*i)++;
	current_final->args[*i] = NULL;
	if (current_final->cmd)
		free(current_final->cmd);
	current_final->cmd = ft_strdup(current_final->args[0]);
	if (current_final->cmd == NULL)
		return (false);
	return (true);
}

char	*ft_unquote_result(char *str, t_args *current)
{
	int		len;
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' && current->quotes != 2) || (str[i] == '\"' && current->quotes != 1))
		{
			i++;
			continue;
		}
		result[j] = str[i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}

// char	*ft_unquote_result(char	*str, t_args *current)
// {
// 	int		len;
// 	char	*result;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	len = ft_strlen(str);// ici avant j'avais -2 car -1 par quote, cette fonction est surement a revoir
// 	result = malloc(sizeof(char) * len + 1);
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && current->quotes != 2)
// 			i++;
// 		if (str[i] == '\"' && current->quotes != 1)
// 			i++;
// 		result[j] = str[i];
// 		j++;
// 		i++;
// 	}
// 	result[j] = '\0';
// 	return (result);
// }