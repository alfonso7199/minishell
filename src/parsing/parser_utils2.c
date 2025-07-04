/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/04 10:07:12 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Llenar array de argumentos */
t_token	*fill_args(t_token *tokens, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != TOKEN_PIPE
		&& tokens->type != TOKEN_SEMICOLON
		&& tokens->type != TOKEN_EOF)
	{
		if (tokens->type == TOKEN_WORD || tokens->type == TOKEN_ENV_VAR
			|| tokens->type == TOKEN_EXIT_STATUS)
		{
			cmd->args[i] = ft_strdup(tokens->value);
			i++;
			tokens = tokens->next;
		}
		else if (is_redirection_token(tokens->type))
			tokens = handle_redirection(tokens, cmd);
		else
			tokens = tokens->next;
		if (!tokens)
			break ;
	}
	cmd->args[i] = NULL;
	return (tokens);
}

bool	validate_syntax(t_token *tokens)
{
	t_token	*current;
	bool	expect_word;

	current = tokens;
	expect_word = false;
	while (current && current->type != TOKEN_EOF)
	{
		if (!validate_syntax_loop(current, &expect_word))
			return (false);
		current = current->next;
	}
	if (expect_word)
		return (false);
	return (true);
}

t_pipeline	*add_new_pipeline(t_pipeline **pipeline_list,
				t_pipeline **current_pipeline)
{
	t_pipeline	*new_pipeline;

	new_pipeline = malloc(sizeof(t_pipeline));
	if (!new_pipeline)
		return (NULL);
	new_pipeline->cmds = NULL;
	new_pipeline->next = NULL;
	if (!*pipeline_list)
		*pipeline_list = new_pipeline;
	else
		(*current_pipeline)->next = new_pipeline;
	*current_pipeline = new_pipeline;
	return (new_pipeline);
}

bool	add_new_cmd(t_pipeline *current_pipeline, t_cmd **current_cmd,
				t_token **current_token)
{
	t_cmd	*new_cmd;

	new_cmd = create_cmd();
	if (!new_cmd)
		return (false);
	*current_token = parse_args(*current_token, new_cmd);
	if (!*current_token)
		return (false);
	if (!current_pipeline->cmds)
		current_pipeline->cmds = new_cmd;
	else
		(*current_cmd)->next = new_cmd;
	*current_cmd = new_cmd;
	return (true);
}
