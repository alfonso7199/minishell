/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/04 12:21:43 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Crear nuevo comando */
t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

/* Crear nueva redirección */
t_redir	*create_redir(t_token_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

bool	validate_syntax_loop(t_token *current, bool *expect_word)
{
	if (*expect_word)
	{
		if (has_redirection_error(current))
			return (false);
		*expect_word = false;
	}
	else if (is_redirection_token(current->type))
		*expect_word = true;
	else if (current->type == TOKEN_PIPE
		|| current->type == TOKEN_SEMICOLON)
	{
		if (has_pipe_semicolon_error(current))
			return (false);
	}
	return (true);
}

static bool	parser_loop(t_token **current_token, t_pipeline **pipeline_list,
					t_pipeline **current_pipeline, t_cmd **current_cmd)
{
	if (!*pipeline_list || (*current_token)->type == TOKEN_SEMICOLON)
	{
		if (!add_new_pipeline(pipeline_list, current_pipeline))
			return (false);
		if ((*current_token)->type == TOKEN_SEMICOLON)
			*current_token = (*current_token)->next;
		*current_cmd = NULL;
	}
	if (*current_token && (*current_token)->type != TOKEN_SEMICOLON
		&& (*current_token)->type != TOKEN_EOF)
	{
		if (!add_new_cmd(*current_pipeline, current_cmd, current_token))
			return (false);
	}
	if (*current_token && (*current_token)->type == TOKEN_PIPE)
		*current_token = (*current_token)->next;
	return (true);
}

t_pipeline	*parser(t_token *tokens)
{
	t_pipeline	*pipeline_list;
	t_pipeline	*current_pipeline;
	t_token		*current_token;
	t_cmd		*current_cmd;

	pipeline_list = NULL;
	current_pipeline = NULL;
	current_token = tokens;
	current_cmd = NULL;
	while (current_token && current_token->type != TOKEN_EOF)
	{
		if (!parser_loop(&current_token, &pipeline_list,
				&current_pipeline, &current_cmd))
			return (pipeline_list);
	}
	return (pipeline_list);
}
