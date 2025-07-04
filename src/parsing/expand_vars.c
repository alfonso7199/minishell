/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/04 12:37:15 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Expandir $? (exit status) */
static char	*expand_exit_status(t_shell *shell)
{
	return (ft_itoa(shell->exit_status));
}

/* Expandir $VAR */
char	*expand_env_var(char *str, t_shell *shell)
{
	char	*var_name;
	char	*value;
	char	*dup;
	int		i;

	if (!str || str[0] != '$')
		return (ft_strdup(str));
	if (str[1] == '?')
		return (expand_exit_status(shell));
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, 1, i - 1);
	if (!var_name)
		return (ft_strdup(""));
	value = get_env_value(shell->env, var_name);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	dup = ft_strdup(value);
	return (dup);
}

/* Expandir variables en string completo */
char	*expand_variables_loop(char *str, t_shell *shell, char *result)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
		{
			if (is_escaped_dollar(str, i))
			{
				result = process_character(result, '$');
				i++;
				continue ;
			}
			result = handle_variable_expansion(str, &i, result, shell);
		}
		else
		{
			result = process_character(result, str[i]);
			i++;
		}
	}
	return (result);
}

static t_token	*expand_token_value(t_token *tokens, t_token *prev,
	t_token **current, t_shell *shell)
{
	char	*expanded;

	if (((*current)->type == TOKEN_WORD || (*current)->type == TOKEN_ENV_VAR
			|| (*current)->type == TOKEN_EXIT_STATUS)
		&& (*current)->quote_type != SINGLE_QUOTE)
	{
		expanded = expand_variables((*current)->value, shell);
		if (expanded && expanded[0] == '\0')
		{
			tokens = remove_empty_token(tokens, prev, current);
			return (tokens);
		}
		else if (expanded)
		{
			free((*current)->value);
			(*current)->value = expanded;
		}
	}
	return (tokens);
}

/* Expandir variables en lista de tokens */
t_token	*expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	prev = NULL;
	while (current)
	{
		tokens = expand_token_value(tokens, prev, &current, shell);
		prev = current;
		if (current)
			current = current->next;
	}
	return (tokens);
}
