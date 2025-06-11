/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:36 by rzt               #+#    #+#             */
/*   Updated: 2025/06/10 13:20:33 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[0] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	print_sorted_env(t_env *envp)
{
	t_env	*curr;

	curr = envp;
	while (curr)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(curr->key, STDOUT_FILENO);
		if (curr->value)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(curr->value, STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		curr = curr->next;
	}
}

int	process_export_arg(char *arg, t_env **envp)
{
	char	*equal_pos;
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (1);
	}
	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
	{
		key = ft_strdup(arg);
		if (!find_env_node(*envp, key))
			add_env_node(envp, key, "");
		free(key);
		return (0);
	}
	key = ft_substr(arg, 0, equal_pos - arg);
	value = ft_strdup(equal_pos + 1);
	if (key && value)
		set_env_value(envp, key, value);
	free(key);
	free(value);
	return (0);
}

int	mini_export(char **args, t_env **envp)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (!args[1])
	{
		print_sorted_env(*envp);
		return (0);
	}
	while (args[i])
	{
		if (process_export_arg(args[i], envp) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
