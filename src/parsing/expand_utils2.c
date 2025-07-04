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

int	is_escaped_dollar(const char *str, int pos)
{
	int	backslash_count;
	int	j;

	backslash_count = 0;
	j = pos - 1;
	while (j >= 0 && str[j] == '\\')
	{
		backslash_count++;
		j--;
	}
	return (backslash_count % 2 == 1);
}

char	*expand_variables(char *str, t_shell *shell)
{
	char	*result;

	if (!str || !shell)
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (expand_variables_loop(str, shell, result));
}
