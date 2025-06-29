/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* Procesar operador */
t_token	*process_operator(char *input, int *i)
{
	char			*value;
	t_token_type	type;

	value = extract_operator(input, i);
	type = get_token_type(value);
	return (create_token(type, value, false, NO_QUOTE));
}

/* Procesar palabra */
t_token	*process_word(char *input, int *i)
{
	char			*value;
	bool			quoted;
	t_quote_state	quote_type;

	value = extract_word(input, i, &quote_type, &quoted);
	if (!value)
		return (NULL);
	return (create_token(TOKEN_WORD, value, quoted, quote_type));
}
