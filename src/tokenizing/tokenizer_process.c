/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/04 12:46:50 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Procesar palabra */
static t_token	*process_word(char *input, int *i)
{
	char			*value;
	bool			quoted;
	t_quote_state	quote_type;
	t_token			*tok;

	value = extract_word(input, i, &quote_type, &quoted);
	if (!value)
		return (NULL);
	tok = create_token(TOKEN_WORD, value, quoted, quote_type);
	free(value);
	return (tok);
}

/* Procesar operador */
static t_token	*process_operator(char *input, int *i)
{
	char			*value;
	t_token_type	type;
	t_token			*tok;

	value = extract_operator(input, i);
	type = get_token_type(value);
	tok = create_token(type, value, false, NO_QUOTE);
	free(value);
	return (tok);
}

/* Obtener siguiente token */
t_token	*get_next_token(char *input, int *i)
{
	if (input[*i] == '|' || input[*i] == '<'
		|| input[*i] == '>' || input[*i] == ';')
		return (process_operator(input, i));
	return (process_word(input, i));
}
