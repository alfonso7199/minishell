/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:08:20 by rzt               #+#    #+#             */
/*   Updated: 2025/06/24 12:23:02 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	**cleanup_partial_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
	return (NULL);
}

int	cleanup_pipes_error(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
	return (1);
}

void	free_partial_array(char **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(array[i]);
		i++;
	}
	free(array);
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
