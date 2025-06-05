/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:33 by rzt               #+#    #+#             */
/*   Updated: 2025/06/05 20:20:16 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_env_node(t_env **head, char *key, char *value)
{
	t_env	*new_node;
	t_env	*tmp;
	
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		free(key);
		free(value);
		return ;
	}
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	
	if (!*head)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	free_env_list(t_env *env_list)
{
	t_env *tmp;

	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->key);
		free(env_list->value);
		free(env_list);
		env_list = tmp;
	}
}

t_env	*mini_env(char **envp)
{
	char	*firstequal;
	char	*key;
	char	*value;
	t_env	*env_list;

	env_list = NULL;
	while (*envp)
	{
		firstequal = ft_strchr(*envp, '=');
		if (firstequal)
		{
		key = ft_substr(*envp, 0, firstequal - *envp);
		value = ft_strdup(firstequal + 1);
		
		add_env_node(&env_list, key, value);		
		}
		envp++;
	}
	return (env_list);
}
