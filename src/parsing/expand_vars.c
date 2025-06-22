/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Expandir $? (exit status) */
char	*expand_exit_status(t_shell *shell)
{
	return (ft_itoa(shell->exit_status));
}

/* Expandir $VAR */
char	*expand_env_var(char *str, t_shell *shell)
{
	char	*var_name;
	char	*value;
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
	value = get_env_value(var_name, shell);
	free(var_name);
	if (value)
		return (value);
	return (ft_strdup(""));
}

/* Expandir variables en string completo */
char	*expand_variables(char *str, t_shell *shell)
{
	char	*result;
	int		i;

	if (!str || !shell)
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
			result = handle_variable_expansion(str, &i, result, shell);
		else
		{
			result = process_character(result, str[i]);
			i++;
		}
	}
	return (result);
}

/* Expandir variables en lista de tokens */
void	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD || current->type == TOKEN_ENV_VAR
			|| current->type == TOKEN_EXIT_STATUS)
		{
			if (current->quote_type != SINGLE_QUOTE)
			{
				expanded = expand_variables(current->value, shell);
				if (expanded)
				{
					free(current->value);
					current->value = expanded;
				}
			}
		}
		current = current->next;
	}
}

/* Expandir parte de variable en string */
char	*expand_variable_part(char *str, int *i, t_shell *shell)
{
	char	*temp;
	char	*var_value;
	int		start;

	start = *i;
	(*i)++;
	if (str[*i] == '?')
		(*i)++;
	else
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
	temp = ft_substr(str, start, *i - start);
	var_value = expand_env_var(temp, shell);
	free(temp);
	return (var_value);
}
