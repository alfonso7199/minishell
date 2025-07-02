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
	if (*tokens && (*tokens)->type == TOKEN_EOF && !(*tokens)->next)
		return (1);
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

	if (check_and_free_empty_tokens(tokens, full_input))
		return (1);
	tokens = expand_tokens(tokens, shell);
	if (is_empty_tokens(tokens))
	{
		free_tokens(tokens);
		free(full_input);
		return (1);
	}
	cmds = parser(tokens);
	free_tokens(tokens);
	return (execute_and_cleanup_cmds(cmds, shell, full_input));
}
