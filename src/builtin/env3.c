/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:33 by rzt               #+#    #+#             */
/*   Updated: 2025/07/04 11:39:30 by rzt              ###   ########.fr       */
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

t_env	*find_env_node(t_env *envp, char *key)
{
	while (envp)
	{
		if (env_key_match(envp->key, key))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

void	set_env_value(t_env **envp, char *key, char *value)
{
	t_env	*node;

	if (!envp || !key || !value)
		return ;
	node = find_env_node(*envp, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
		return ;
	}
	add_env_node(envp, key, value);
}

int	count_env_vars(t_env *envp)
{
	int		count;

	count = 0;
	while (envp)
	{
		count++;
		envp = envp->next;
	}
	return (count);
}

char	*create_env_string(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}
