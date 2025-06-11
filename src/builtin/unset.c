/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:35 by rzt               #+#    #+#             */
/*   Updated: 2025/06/10 13:20:47 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_unset_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	remove_env_node(t_env **envp, char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!envp || !*envp || !key)
		return ;
	curr = *envp;
	prev = NULL;
	while (curr)
	{
		if (env_key_match(curr->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				*envp = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	mini_unset(char **args, t_env **envp)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (!args[1])
		return (0);
	while (args[i])
	{
		if (!is_valid_unset_identifier(args[i]))
		{
			print_unset_error(args[i]);
			exit_status = 1;
		}
		else
			remove_env_node(envp, args[i]);
		i++;
	}
	return (exit_status);
}
