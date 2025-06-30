/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* Verificar si token es redirección */
bool	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

/* Validar sintaxis básica */
bool	validate_syntax(t_token *tokens)
{
	t_token	*current;
	bool	expect_word;

	current = tokens;
	expect_word = false;
	while (current && current->type != TOKEN_EOF)
	{
		if (expect_word)
		{
			if (current->type != TOKEN_WORD)
				return (false);
			expect_word = false;
		}
		else if (is_redirection_token(current->type))
			expect_word = true;
		else if (current->type == TOKEN_PIPE
			|| current->type == TOKEN_SEMICOLON)
		{
			if (!current->next || current->next->type == TOKEN_EOF)
				return (false);
		}
		current = current->next;
	}
	return (!expect_word);
}

/* Función principal del parser */
t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_token	*current_token;

	if (!tokens || !validate_syntax(tokens))
		return (NULL);
	cmd_list = NULL;
	current_token = tokens;
	while (current_token && current_token->type != TOKEN_EOF)
	{
		current_token = process_command_token(&cmd_list, current_token);
		if (!current_token)
			return (NULL);
		if (current_token && (current_token->type == TOKEN_PIPE
				|| current_token->type == TOKEN_SEMICOLON))
			current_token = current_token->next;
	}
	return (cmd_list);
}
