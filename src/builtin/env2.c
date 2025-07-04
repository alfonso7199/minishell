/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:33 by rzt               #+#    #+#             */
/*   Updated: 2025/07/04 11:37:38 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_key_match(char *env_key, char *search_key)
{
	size_t	env_len;
	size_t	search_len;

	env_len = ft_strlen(env_key);
	search_len = ft_strlen(search_key);
	if (env_len != search_len)
		return (0);
	return (ft_strncmp(env_key, search_key, search_len) == 0);
}

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

static void	add_to_end(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	add_env_node(t_env **head, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	add_to_end(head, new_node);
}

char	*get_env_value(t_env *envp, char *key)
{
	if (!envp || !key)
		return (NULL);
	while (envp)
	{
		if (env_key_match(envp->key, key))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}
