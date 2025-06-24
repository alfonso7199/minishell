/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:33 by rzt               #+#    #+#             */
/*   Updated: 2025/06/24 17:23:25 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->key);
		free(env_list->value);
		free(env_list);
		env_list = tmp;
	}
}

void	process_env_entry(char *env_str, t_env **env_lst)
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
	return (env_lst);
}
