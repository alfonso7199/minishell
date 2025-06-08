/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_extract.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Extraer palabra considerando comillas */
char	*extract_word(char *input, int *i, t_quote_state *quote_type,
			bool *quoted)
{
	int		start;

	start = *i;
	*quoted = false;
	*quote_type = NO_QUOTE;
	if (is_quote(input[*i]))
	{
		*quoted = true;
		handle_quoted_word(input, i, &start, quote_type);
	}
	else
		handle_unquoted_word(input, i);
	return (ft_substr(input, start, *i - start));
}

/* Extraer operador (|, <, >, <<, >>) */
char	*extract_operator(char *input, int *i)
{
	int	start;
	int	len;

	start = *i;
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
	{
		*i += 2;
		len = 2;
	}
	else
	{
		(*i)++;
		len = 1;
	}
	return (ft_substr(input, start, len));
}

/* Extraer variable de entorno */
char	*extract_env_var(char *input, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("$?"));
	}
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	return (ft_substr(input, start, *i - start));
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
	return (create_token(TOKEN_WORD, value, quoted, quote_type));
}
