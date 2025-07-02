/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/06/26 11:36:57 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*remove_empty_token(t_token *tokens, t_token *prev,
	t_token **current)
{
	t_token	*tmp;

	tmp = (*current)->next;
	if (prev)
		prev->next = tmp;
	else
		tokens = tmp;
	free((*current)->value);
	free(*current);
	*current = tmp;
	return (tokens);
}
