/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:19:53 by rzt               #+#    #+#             */
/*   Updated: 2025/06/30 14:18:47 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_for_child(pid_t pid, int *status)
{
	int	exit_code;

	if (waitpid(pid, status, 0) == -1)
		return (1);
	if (WIFEXITED(*status))
		exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		exit_code = 128 + WTERMSIG(*status);
	else
		exit_code = 1;
	return (exit_code);
}

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
