/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:33 by rzt               #+#    #+#             */
/*   Updated: 2025/06/05 16:43:11 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(const char **envp)
{
	char	*firstequal;
	char	*key;
	char	*value;

	while (*envp)
	{
		firstequal = ft_strchr(*envp, '=');
		if (firstequal)
		{
		key = ft_substr(*envp, 0, firstequal - *envp);
		value = ft_strdup(firstequal + 1);
		
		ft_putstr_fd(key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		
		free(key);
		free(value);
		}
		envp++;
	}
	return (0);
}