/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:08:20 by rzt               #+#    #+#             */
/*   Updated: 2025/06/26 12:16:07 by rzt              ###   ########.fr       */
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
