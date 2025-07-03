/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/03 20:23:54 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_and_free_empty_tokens(t_token *tokens, char *full_input)
{
	if (is_empty_tokens(tokens))
	{
		free(full_input);
		return (1);
	}
	return (0);
}

t_token	*expand_and_check_tokens(t_token *tokens, char *full_input)
{
	tokens = expand_tokens(tokens, NULL);
	if (is_empty_tokens(tokens))
	{
		free_tokens(tokens);
		free(full_input);
		return (NULL);
	}
	return (tokens);
}

int	execute_and_cleanup_cmds(t_cmd *cmds, t_shell *shell, char *full_input)
{
	if (!cmds)
	{
		write(2, "minishell: syntax error\n", 24);
		free(full_input);
		return (0);
	}
	setup_signals(EXECUTION_MODE);
	execute_commands(cmds, shell);
	setup_signals(INTERACTIVE_MODE);
	clear_signal_received();
	free_cmd_list(cmds);
	free(full_input);
	set_secondary_prompt(0);
	return (1);
}

int	expand_and_check_tokens_internal(t_token **tokens, t_shell *shell,
		char *full_input)
{
	*tokens = expand_tokens(*tokens, shell);
	if (is_empty_tokens(*tokens))
	{
		free_tokens(*tokens);
		free(full_input);
		return (1);
	}
	return (0);
}

void	execute_all_pipelines(t_pipeline *pipelines, t_shell *shell)
{
	t_pipeline	*current_pipeline;
	int			last_status;

	current_pipeline = pipelines;
	while (current_pipeline)
	{
		last_status = 0;
		if (current_pipeline->cmds && current_pipeline->cmds->next)
			last_status = execute_pipeline(current_pipeline->cmds, shell);
		else if (current_pipeline->cmds)
			last_status = execute_single_cmd(current_pipeline->cmds, shell);
		shell->exit_status = last_status;
		current_pipeline = current_pipeline->next;
	}
}
