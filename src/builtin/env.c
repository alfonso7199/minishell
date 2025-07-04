/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:33 by rzt               #+#    #+#             */
/*   Updated: 2025/07/04 11:36:30 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	swap_env_nodes(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	sort_env_list(t_env *env)
{
	int		swapped;
	t_env	*ptr;
	t_env	*last;

	last = NULL;
	if (!env)
		return ;
	while (1)
	{
		swapped = 0;
		ptr = env;
		while (ptr->next != last)
		{
			if (ft_strncmp(ptr->key, ptr->next->key,
					ft_strlen(ptr->next->key)) > 0)
			{
				swap_env_nodes(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		last = ptr;
		if (!swapped)
			break ;
	}
}

static void	process_env_entry(char *env_str, t_env **env_lst)
{
	char	*equal_pos;
	char	*key;
	char	*value;

	equal_pos = ft_strchr(env_str, '=');
	if (!equal_pos)
		return ;
	key = ft_substr(env_str, 0, equal_pos - env_str);
	value = ft_strdup(equal_pos + 1);
	if (key && value)
		add_env_node(env_lst, key, value);
	free(key);
	free(value);
}

t_env	*mini_env(char **envp)
{
	t_env	*env_lst;

	env_lst = NULL;
	while (*envp)
	{
		process_env_entry(*envp, &env_lst);
		envp++;
	}
	increment_shlvl(&env_lst);
	sort_env_list(env_lst);
	return (env_lst);
}

int	mini_env_print(t_env *envp)
{
	t_env	*current;

	if (!envp)
		return (1);
	current = envp;
	while (current)
	{
		ft_putstr_fd(current->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
	return (0);
}
