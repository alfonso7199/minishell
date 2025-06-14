/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Manejar palabra con comillas */
void	handle_quoted_word(char *input, int *i, int *start,
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
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (input[*i] == quote_char)
		(*i)++;
}

/* Manejar palabra sin comillas */
void	handle_unquoted_word(char *input, int *i)
{
	while (input[*i] && !is_special_char(input[*i])
		&& !is_quote(input[*i]))
		(*i)++;
}
