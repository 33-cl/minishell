/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:16:24 by maeferre          #+#    #+#             */
/*   Updated: 2024/06/10 18:53:51 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
    Reproduit la commande pwd

    Renvoie 1 en cas d'erreur de getcwd
*/

int pwd(void)
{
    char    *cwd;

    cwd = getcwd(NULL, 0);
    //ajouter protection
    if (!cwd)
        return (1);
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}
