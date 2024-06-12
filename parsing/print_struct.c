/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:36:06 by qordoux           #+#    #+#             */
/*   Updated: 2024/05/29 17:17:00 by maeferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_string_array(char **array) {
    if (array == NULL) {
        printf("(null)");
        return;
    }
    for (int i = 0; array[i] != NULL; i++) {
        printf("%s", array[i]);
        if (array[i + 1] != NULL) {
            printf("; ");  // Ajoute un point-virgule entre les éléments
        }
    }
}

// Fonction pour imprimer un nœud de la liste t_cmd de manière sécurisée
void print_final_node(t_cmd *node) {
    if (node == NULL) {
        printf("Node is NULL\n");
        return;
    }

    printf("Command: %s\n", node->cmd ? node->cmd : "(null)");

    printf("Arguments: ");
    if (node->args) {
        print_string_array(node->args);
    } else {
        printf("(null)");
    }
    printf("\n");

    printf("Heredoc Delimiters: ");
    if (node->heredoc_delimiters) {
        print_string_array(node->heredoc_delimiters);
    } else {
        printf("(null)");
    }
    printf("\n");

    printf("Number of Heredocs: %d\n", node->nb_heredocs);
    printf("Heredoc FD: %d\n", node->fd_heredoc);

    printf("Redirections: ");
    if (node->redir) {
        print_string_array(node->redir);
    } else {
        printf("(null)");
    }
    printf("\n");

    printf("-------------------\n");
}

// Fonction pour imprimer tous les nœuds de la liste t_cmd de manière sécurisée
// void print_final_list(t_cmd *list) {
//     t_cmd *current = list;
//     while (current != NULL) {
//         print_final_node(current);
//         current = current->next;
//     }
// }

void print_final_list(t_cmd *list)
{
    t_cmd *current = list;
    int node_index = 0;  // Compteur de nœuds
    while (current != NULL) {
        printf("Node %d:\n", node_index);  // Imprime le numéro de nœud
        print_final_node(current);
        current = current->next;
        node_index++;
    }
}

// void print_args(t_args *args) {
//     if (args == NULL) {
//         printf("None\n");
//         return;
//     }
//     printf("[ ");
//     while (args != NULL) {
//         printf("{ Value: \"%s\", Type: %d, Quotes: %d }", args->value, args->type, args->quotes);
//         args = args->next;
//         if (args != NULL) printf(", ");
//     }
//     printf(" ]\n");
// }

void print_args(t_args *args) {
    if (args == NULL) {
        printf("None\n");
        return;
    }
    printf("[ ");
    while (args != NULL) {
        printf("{ Value: \"%s\", Type: %d, Quotes: %d", args->value, args->type, args->quotes);
        if (args->multi_quoted_args != NULL) {
            printf(", Multi-Quoted Args: ");
            print_args(args->multi_quoted_args);
        }
        printf(" }");
        args = args->next;
        if (args != NULL) printf(", ");
    }
    printf(" ]\n");
}

void print_command_details(t_command *command, t_env *env)
{
    t_command *current = command;
    int count = 0;

    // Print environment variables
    // print_env(env);
	(void)env;
    while (current != NULL) {
        printf("Command %d:\n", ++count);
        printf("  cmd: \"%s\"\n", current->cmd ? current->cmd : "None");

        printf("  args: ");
        print_args(current->args);

        printf("  Redirections:\n    in: ");
        print_string_array(current->redir);
        printf("\n");

        printf("  heredoc_delimiters: ");
        print_string_array(current->heredoc_delimiters);
        printf("\n");

        printf("  nb_heredocs: %d\n", current->nb_heredocs);

        current = current->next;
        if (current != NULL) {
            printf("\n");
        }
    }
}


// void print_string_array(char **array) {
//     if (array) {
//         printf("[ ");
//         for (int i = 0; array[i] != NULL; i++) {
//             printf("\"%s\"", array[i]);
//             if (array[i + 1] != NULL)
//                 printf(", ");
//         }
//         printf(" ]");
//     } else {
//         printf("None");
//     }
//     printf("\n");
// }