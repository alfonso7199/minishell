/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/06/26 16:40:55 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

void	print_commands(t_cmd *cmds)
{
	int		i;
	t_redir *r;

	i = 0;
	while (cmds)
	{
		printf("Command %d:\n", ++i);
		printf("  Args: ");
		for (int j = 0; cmds->args[j]; j++)
			printf("%s ", cmds->args[j]);
		printf("\n");
		printf("  Redirections:\n");
		r = cmds->redirections;
		while (r)
		{
			printf("    Type: %d, File: %s\n", r->type, r->file);
			r = r->next;
		}
		cmds = cmds->next;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_shell	*shell;
	t_token	*tokens;
	t_cmd	*cmds;

	if (argc != 1 || argv[1])
		printf("This program does not accept arguments\n");
	shell = init_shell(envp);
	if (!shell)
		return (1);
	setup_signals(INTERACTIVE_MODE);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = tokenizer(input);
		if (!tokens)
		{
			printf("Error en tokenizer\n");
			free(input);
			continue ;
		}
		cmds = parser(tokens);
		free_tokens(tokens);
		if (!cmds)
		{
			printf("Error en parser\n");
			free(input);
			continue ;
		}
		print_commands(cmds);
		execute_commands(cmds, shell);
		free_cmd_list(cmds);
		free(input);
	}
	cleanup_shell(shell);
	return (0);
}
