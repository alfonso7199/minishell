/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:30:00 by rzt               #+#    #+#             */
/*   Updated: 2025/06/27 14:30:00 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_input_line(char *full_input)
{
	char	*input;

	restore_terminal();
	if (full_input[0] == '\0')
	{
		set_secondary_prompt(0);
		setup_interactive_signals();
		input = readline("minishell> ");
	}
	else
	{
		set_secondary_prompt(1);
		setup_secondary_prompt_signals();
		input = readline("> ");
	}
	return (input);
}

static int	process_input_line(char **full_input, t_token **tokens)
{
	char	*input;
	int		signal_result;

	input = get_input_line(*full_input);
	if (!input)
		return (0);
	if (input[0] == '\0')
	{
		free(input);
		return (2);
	}
	signal_result = handle_input_signal(full_input, input);
	if (signal_result != 0)
		return (signal_result);
	concatenate_input(full_input, input);
	*tokens = tokenizer(*full_input);
	if (*tokens)
		return (1);
	set_secondary_prompt(1);
	return (2);
}

int	handle_input_loop(char **full_input, t_token **tokens)
{
	int	result;

	while (1)
	{
		result = process_input_line(full_input, tokens);
		if (result == 0 || result == -1)
			return (result);
		if (result == 1)
			break ;
	}
	return (1);
}

int	process_command(t_token *tokens, t_shell *shell, char *full_input)
{
	t_cmd	*cmds;

	if (!tokens || !tokens->value || tokens->value[0] == '\0')
	{
		free(full_input);
		return (1);
	}
	expand_tokens(tokens, shell);
	cmds = parser(tokens);
	free_tokens(tokens);
	if (!cmds)
	{
		printf("Error en parser\n");
		free(full_input);
		return (0);
	}
	execute_commands(cmds, shell);
	free_cmd_list(cmds);
	free(full_input);
	set_secondary_prompt(0);
	return (1);
}
