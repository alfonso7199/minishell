/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:33 by rzt               #+#    #+#             */
/*   Updated: 2025/06/05 16:33:16 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(const char **envp)
{
	char	**split;
	char	*key;
	char	*value;
	int		i;

	while (*envp)
	{
		split = ft_split(*envp, '=');
		key = ft_strdup(split[0]);
		value = ft_strdup(split[1]);
		ft_putstr_fd(key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		
		free(key);
		free(value);
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		envp++;
	}
	return (0);
}