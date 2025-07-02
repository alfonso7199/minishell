/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/02 12:00:09 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Crear un nuevo token, nodo de una lista enlazada */
t_token	*create_token(t_token_type type, char *value, bool quoted,
			t_quote_state quote_type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->quoted = quoted;
	new_token->quote_type = quote_type;
	new_token->next = NULL;
	return (new_token);
}

/* Verificar si es caracter especial */
bool	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';' || c == ' '
		|| c == '\t' || c == '\n' || c == '\0' || c == '`');
}

/* Verificar si es comilla */
bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/* Función principal, de string a lista enlazada de tokens */
t_token	*tokenizer(char *input)
{
	t_token	*tokens;
	t_token	*new_token;
	int		i;

	if (!input)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break ;
		new_token = get_next_token(input, &i);
		if (!new_token)
		{
			free_tokens(tokens);
			return (NULL);
		}
		add_token_to_list(&tokens, new_token);
	}
	new_token = create_token(TOKEN_EOF, "", false, NO_QUOTE);
	if (new_token)
		add_token_to_list(&tokens, new_token);
	return (tokens);
}

/* Liberar lista de tokens */
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}
