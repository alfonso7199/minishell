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

/* Obtener valor de variable de entorno */
// char	*get_env_value(char *var_name, t_shell *shell)
// {
// 	int		i;
// 	char	*key;
// 	int		key_len;

// 	if (!var_name || !shell || !shell->env)
// 		return (NULL);
// 	i = 0;
// 	key_len = ft_strlen(var_name);
// 	while (shell->env[i])
// 	{
// 		if (ft_strncmp(shell->env[i], var_name, key_len) == 0
// 			&& shell->env[i][key_len] == '=')
// 		{
// 			key = ft_strdup(shell->env[i] + key_len + 1);
// 			return (key);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

/* Expandir un carácter al resultado */
char	*expand_char(char *result, char c)
{
	char	*temp;
	char	char_arr[2];

	if (!result)
		return (NULL);
	char_arr[0] = c;
	char_arr[1] = '\0';
	temp = result;
	result = ft_strjoin(result, char_arr);
	free(temp);
	return (result);
}

/* Procesar variable individual */
char	*process_variable(char *str, int *i, t_shell *shell)
{
	char	*var_value;

	var_value = expand_variable_part(str, i, shell);
	if (var_value)
		return (var_value);
	return (ft_strdup(""));
}

/* Procesar carácter individual */
char	*process_character(char *result, char c)
{
	result = expand_char(result, c);
	return (result);
}

/* Manejar expansión de variable completa */
char	*handle_variable_expansion(char *str, int *i, char *result,
			t_shell *shell)
{
	char	*temp;
	char	*var_value;

	var_value = process_variable(str, i, shell);
	temp = result;
	result = ft_strjoin(result, var_value);
	free(temp);
	free(var_value);
	return (result);
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
