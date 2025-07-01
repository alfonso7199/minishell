/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:19:45 by rzt               #+#    #+#             */
/*   Updated: 2025/07/01 17:25:54 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	increment_shlvl(t_env **envp)
{
	t_env	*node;
	char	*new_shlvl;
	int		lvl;

	node = find_env_node(*envp, "SHLVL");
	if (!node)
	{
		add_env_node(envp, "SHLVL", "1");
		return ;
	}
	lvl = ft_atoi(node->value);
	lvl++;
	new_shlvl = ft_itoa(lvl);
	if (!new_shlvl)
		return ;
	set_env_value(envp, "SHLVL", new_shlvl);
	free(new_shlvl);
}
