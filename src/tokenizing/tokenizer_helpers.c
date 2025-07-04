/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/04 11:46:13 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_quoted_word_loop(char *input, int *i,
				t_quote_state quote_type, char quote_char)
{
	while (input[*i] && input[*i] != quote_char)
	{
		if (quote_type == SINGLE_QUOTE)
		{
			(*i)++;
			continue ;
		}
		if (quote_type == DOUBLE_QUOTE && input[*i] == '\\' && input[*i + 1])
		{
			if (input[*i + 1] == '"' || input[*i + 1] == '\\'
				|| input[*i + 1] == '$' || input[*i + 1] == '`')
			{
				(*i) += 2;
				continue ;
			}
			else
			{
				(*i)++;
				continue ;
			}
		}
		(*i)++;
	}
}

bool	handle_quoted_word(char *input, int *i, int *start,
			t_quote_state *quote_type)
{
	char	quote_char;

	quote_char = input[*i];
	if (quote_char == '\'')
		*quote_type = SINGLE_QUOTE;
	else
		*quote_type = DOUBLE_QUOTE;
	(*i)++;
	*start = *i;
	handle_quoted_word_loop(input, i, *quote_type, quote_char);
	if (input[*i] == quote_char)
	{
		(*i)++;
		return (true);
	}
	return (false);
}

/* Manejar palabra sin comillas */
void	handle_unquoted_word(char *input, int *i)
{
	while (input[*i] && !is_special_char(input[*i])
		&& !is_quote(input[*i]))
		(*i)++;
}

static void	process_escape_sequence(char *str, int *i, char *result, int *j)
{
	if (str[*i + 1] == '"' || str[*i + 1] == '\\'
		|| str[*i + 1] == '$' || str[*i + 1] == '`')
	{
		result[*j] = str[*i + 1];
		(*j)++;
		*i += 2;
	}
	else
	{
		result[*j] = str[*i];
		(*j)++;
		(*i)++;
		result[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
}

char	*process_escapes_in_quotes(char *str, t_quote_state quote_type)
{
	char	*result;
	int		i;
	int		j;

	if (quote_type == SINGLE_QUOTE)
		return (ft_strdup(str));
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
			process_escape_sequence(str, &i, result, &j);
		else
		{
			result[j] = str[i];
			j++;
			i++;
		}
	}
	result[j] = '\0';
	return (result);
}
