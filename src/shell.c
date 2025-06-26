/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:14:03 by rzt               #+#    #+#             */
/*   Updated: 2025/06/26 12:16:15 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell_values(t_shell *shell)
{
	shell->exit_status = 0;
	shell->cmd_list = NULL;
}

int	validate_shell_env(t_shell *shell)
{
	if (!shell->env)
	{
		free(shell);
		return (0);
	}
	return (1);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = mini_env(envp);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	shell->exit_status = 0;
	shell->cmd_list = NULL;
	return (shell);
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		free_env_list(shell->env);
	if (shell->cmd_list)
		free_cmd_list(shell->cmd_list);
	free(shell);
}
