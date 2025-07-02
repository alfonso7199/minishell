/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_extract_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/02 12:13:58 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_quoted_fragment(char *input, int *i, t_word_ctx *ctx)
{
	ctx->fragment = extract_quoted_word(input, i, &ctx->qt_tmp,
			&ctx->quoted_tmp);
	if (!ctx->fragment)
		return (0);
	if (ctx->qt_tmp != SINGLE_QUOTE)
		ctx->only_single_quote = false;
	if (ctx->qt_tmp != NO_QUOTE)
		*(ctx->quoted) = true;
	ctx->result = ft_strjoin_free(ctx->result, ctx->fragment);
	free(ctx->fragment);
	return (1);
}

static int	process_unquoted_fragment(char *input, int *i, t_word_ctx *ctx)
{
	ctx->only_single_quote = false;
	ctx->start = *i;
	handle_unquoted_word(input, i);
	ctx->fragment = ft_substr(input, ctx->start, *i - ctx->start);
	if (!ctx->fragment)
		return (0);
	ctx->result = ft_strjoin_free(ctx->result, ctx->fragment);
	free(ctx->fragment);
	return (1);
}

static int	extract_word_loop(char *input, int *i, t_word_ctx *ctx)
{
	while (input[*i] && !is_special_char(input[*i]))
	{
		if (is_quote(input[*i]))
		{
			if (!process_quoted_fragment(input, i, ctx))
				return (0);
		}
		else
		{
			if (!process_unquoted_fragment(input, i, ctx))
				return (0);
		}
	}
	return (1);
}

char	*extract_word_body(char *input, int *i, t_quote_state *quote_type,
			bool *quoted)
{
	t_word_ctx	ctx;

	ctx.result = ft_strdup("");
	ctx.only_single_quote = true;
	ctx.quote_type = quote_type;
	ctx.quoted = quoted;
	*(ctx.quoted) = false;
	*(ctx.quote_type) = NO_QUOTE;
	if (!ctx.result)
		return (NULL);
	if (!extract_word_loop(input, i, &ctx))
	{
		free(ctx.result);
		return (NULL);
	}
	if (*(ctx.quoted) && ctx.only_single_quote)
		*(ctx.quote_type) = SINGLE_QUOTE;
	return (ctx.result);
}
