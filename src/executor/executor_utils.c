/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:19:53 by rzt               #+#    #+#             */
/*   Updated: 2025/06/23 18:34:47 by rzt              ###   ########.fr       */
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

int	handle_command_not_found(char *cmd_name)
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

int	handle_fork_error(void)
{
	ft_putstr_fd("minishell: fork filed\n", STDERR_FILENO);
	return (1);
}

void	print_file_error(char *filename, char *error_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
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
