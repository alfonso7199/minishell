/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_extract.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/06/26 17:53:59 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_quoted_word(char *input, int *i, t_quote_state *quote_type,
			bool *quoted)
{
	int		start;
	int		end;
	bool	quotes_closed;
	char	*raw_str;
	char	*processed_str;

	start = *i;
	*quoted = true;
	quotes_closed = handle_quoted_word(input, i, &start, quote_type);
	if (!quotes_closed)
		return (NULL);
	end = *i;
	if (end > start && input[end - 1] == '\'' && *quote_type == SINGLE_QUOTE)
		end--;
	else if (end > start && input[end - 1] == '"'
		&& *quote_type == DOUBLE_QUOTE)
		end--;
	raw_str = ft_substr(input, start, end - start);
	if (!raw_str)
		return (NULL);
	processed_str = process_escapes_in_quotes(raw_str, *quote_type);
	free(raw_str);
	return (processed_str);
}

static char	*extract_unquoted_word(char *input, int *i)
{
	int	start;

	start = *i;
	handle_unquoted_word(input, i);
	return (ft_substr(input, start, *i - start));
}

/* Extraer palabra considerando comillas */
char	*extract_word(char *input, int *i, t_quote_state *quote_type,
			bool *quoted)
{
	*quoted = false;
	*quote_type = NO_QUOTE;
	if (is_quote(input[*i]))
		return (extract_quoted_word(input, i, quote_type, quoted));
	else
		return (extract_unquoted_word(input, i));
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
