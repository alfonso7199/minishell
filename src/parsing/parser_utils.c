/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Añadir redirección a comando */
void	add_redir_to_cmd(t_cmd *cmd, t_redir *redir)
{
	t_redir	*current;

	if (!cmd->redirections)
	{
		cmd->redirections = redir;
		return ;
	}
	current = cmd->redirections;
	while (current->next)
		current = current->next;
	current->next = redir;
}

/* Contar argumentos en lista de tokens */
int	count_args(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && current->type != TOKEN_PIPE
		&& current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_WORD)
			count++;
		else if (is_redirection_token(current->type))
		{
			current = current->next;
			if (!current)
				break ;
		}
		current = current->next;
	}
	return (count);
}

/* Manejar redirección en parsing */
t_token	*handle_redirection(t_token *tokens, t_cmd *cmd)
{
	t_token_type	redir_type;
	t_redir			*redir;

	redir_type = tokens->type;
	tokens = tokens->next;
	if (!tokens || tokens->type != TOKEN_WORD)
		return (NULL);
	redir = create_redir(redir_type, tokens->value);
	if (!redir)
		return (NULL);
	add_redir_to_cmd(cmd, redir);
	return (tokens->next);
}

/* Añadir comando a la lista */
void	add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		return ;
	}
	current = *cmd_list;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

/* Parsear argumentos de un comando */
t_token	*parse_args(t_token *tokens, t_cmd *cmd)
{
	int	arg_count;

	arg_count = count_args(tokens);
	if (arg_count == 0)
		return (tokens);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return (NULL);
	return (fill_args(tokens, cmd));
}
