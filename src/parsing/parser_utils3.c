/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_redirection_error(t_token *current)
{
	if (current->type != TOKEN_WORD)
		return (true);
	return (false);
}

bool	has_pipe_semicolon_error(t_token *current)
{
	if (!current->next || current->next->type == TOKEN_EOF)
		return (true);
	return (false);
}

/* Verificar si token es redirección */
bool	is_redirection_token(t_token_type type)
{
	if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		return (true);
	return (false);
}
