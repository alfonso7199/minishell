/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/06/10 16:48:19 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *tokens) {
    while (tokens) {
        printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
        tokens = tokens->next;
    }
}

void print_commands(t_cmd *cmds) {
    int i = 0;
    while (cmds) {
        printf("Command %d:\n", ++i);
        printf("  Args: ");
        for (int j = 0; cmds->args[j]; j++)
            printf("%s ", cmds->args[j]);
        printf("\n");
        printf("  Redirections:\n");
        t_redir *r = cmds->redirections;
        while (r) {
            printf("    Type: %d, File: %s\n", r->type, r->file);
            r = r->next;
        }
        cmds = cmds->next;
    }
}

int main(int argc, char *argv[], char *envp[])
{
    char    *input;
    // t_env   *env_lst;
    // int     exit_status;

    (void)envp;
    if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}    
    while (1) {
        input = readline("minishell> ");
        if (!input)
            break;
        add_history(input);
/* 
        t_token *tokens = tokenizer(input);
        if (!tokens) {
            printf("Error en tokenizer\n");
            free(input);
            continue;
        }
        t_cmd *cmds = parser(tokens);
        if (!cmds) {
            printf("Error en parser\n");
            free(input);
            continue;
        }
        print_commands(cmds); 
 */
        free(input);
    }
    return 0;
}