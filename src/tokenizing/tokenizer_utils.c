/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Añadir token al final de la lista */
void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

/* Obtener tipo de token según el caracter */
t_token_type	get_token_type(char *str)
{
	if (!str || !*str)
		return (TOKEN_EOF);
	if (str[0] == '|')
		return (TOKEN_PIPE);
	if (str[0] == '<' && str[1] == '<')
		return (TOKEN_HEREDOC);
	if (str[0] == '<')
		return (TOKEN_REDIR_IN);
	if (str[0] == '>' && str[1] == '>')
		return (TOKEN_APPEND);
	if (str[0] == '>')
		return (TOKEN_REDIR_OUT);
	if (str[0] == '$' && str[1] == '?')
		return (TOKEN_EXIT_STATUS);
	if (str[0] == '$')
		return (TOKEN_ENV_VAR);
	return (TOKEN_WORD);
}

/* Saltar espacios en blanco */
void	skip_whitespace(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
}

/* Obtener siguiente token */
t_token	*get_next_token(char *input, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	if (input[*i] == '$')
		new_token = process_env_var(input, i);
	else if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		new_token = process_operator(input, i);
	else
		new_token = process_word(input, i);
	return (new_token);
}

/* Procesar variable de entorno */
t_token	*process_env_var(char *input, int *i)
{
	char			*value;
	t_token_type	type;

	value = extract_env_var(input, i);
	type = get_token_type(value);
	return (create_token(type, value, false, NO_QUOTE));
}
