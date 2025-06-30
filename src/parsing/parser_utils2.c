/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
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

/* Procesar token de comando */
t_token	*process_command_token(t_cmd **cmd_list, t_token *token)
{
	t_cmd	*current_cmd;

	current_cmd = create_cmd();
	if (!current_cmd)
	{
		free_cmd_list(*cmd_list);
		return (NULL);
	}
	token = parse_args(token, current_cmd);
	if (!token)
	{
		free_cmd_list(*cmd_list);
		return (NULL);
	}
	add_cmd_to_list(cmd_list, current_cmd);
	return (token);
}
