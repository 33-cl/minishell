/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:21:51 by maeferre          #+#    #+#             */
/*   Updated: 2024/05/30 14:01:30 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Renvoie le nombre de flags '-n' a ignorer
*/

static int	number_flags(char **args)
{
	int		i;
	size_t	j;
	
	i = 1;
	while (args[i])
	{
		if (ft_strlen(args[i]) < 2)
			return (i - 1);
		if (args[i][0] != '-')
			return (i - 1);
		j = 0;
		while (j++, args[i][j])
			if (args[i][j] != 'n')
				return (i - 1);
		i++;
	}
	return (i - 1);
}

/*
	Reproduction de la commande echo
	"echo -n" retire le '\n' a la fin du print
*/

void    echo(t_cmd *command)
{
	int	nb_args;
	int	i;

	i = 1 + number_flags(command->args);
	nb_args = ft_tablen(command->args);
	if (nb_args == 0)
		return ;
	while (i < nb_args)
	{
		printf("%s", command->args[i]);
		if (nb_args > i + 1)
			printf(" ");
		i++;
	}
	if (nb_args == 1 || (nb_args >= 2 && !number_flags(command->args)))
		printf("\n");
}
