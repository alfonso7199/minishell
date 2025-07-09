/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:07:23 by rzt               #+#    #+#             */
/*   Updated: 2025/07/09 12:49:52 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	setup_pipeline_redirections(int **pipes, int cmd_index, int pipe_count)
{
	if (cmd_index > 0)
	{
		if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
			exit(1);
	}
	if (cmd_index < pipe_count)
	{
		if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
			exit(1);
	}
}

void	close_all_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	wait_for_pipeline(pid_t	*pids, int cmd_count)
{
	int	i;
	int	status;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (i < cmd_count)
	{
		if (waitpid(pids[i], &status, 0) != -1)
		{
			if (i == cmd_count - 1)
				exit_status = get_exit_status(status);
		}
		i++;
	}
	return (exit_status);
}

void	cleanup_pipeline(int **pipes, pid_t *pids, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(pids);
}
