/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:30:00 by rzt               #+#    #+#             */
/*   Updated: 2025/07/03 20:31:04 by rzt              ###   ########.fr       */
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
	signal_result = handle_input_signal(full_input, input);
	if (signal_result == -1)
	{
		return (-1);
	}
	if (input[0] == '\0')
	{
		free(input);
		return (2);
	}
	concatenate_input(full_input, input);
	cut_whitespaces(*full_input);
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

void	free_all_pipelines(t_pipeline *pipelines)
{
	t_pipeline	*current_pipeline;
	t_pipeline	*next;

	current_pipeline = pipelines;
	while (current_pipeline)
	{
		next = current_pipeline->next;
		free_cmd_list(current_pipeline->cmds);
		free(current_pipeline);
		current_pipeline = next;
	}
}

int	process_command(t_token *tokens, t_shell *shell, char *full_input)
{
	t_pipeline	*pipelines;
	int			result;

	result = 1;
	if (check_and_free_empty_tokens(tokens, full_input))
		return (1);
	if (expand_and_check_tokens_internal(&tokens, shell, full_input))
		return (1);
	pipelines = parser(tokens);
	free_tokens(tokens);
	setup_signals(EXECUTION_MODE);
	execute_all_pipelines(pipelines, shell);
	setup_signals(INTERACTIVE_MODE);
	clear_signal_received();
	free_all_pipelines(pipelines);
	free(full_input);
	return (result);
}
