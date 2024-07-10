/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odx <odx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:49:59 by odx               #+#    #+#             */
/*   Updated: 2024/07/07 10:50:13 by odx              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_heredoc_delimiters(char **heredoc_delimiters)
{
	int	i;

	i = 0;
	while (heredoc_delimiters[i] != NULL)
	{
		free(heredoc_delimiters[i]);
		heredoc_delimiters[i] = NULL;
		i++;
	}
	free(heredoc_delimiters);
}
