/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:42:56 by rzt               #+#    #+#             */
/*   Updated: 2025/07/04 09:59:27 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	execute_commands(t_cmd *cmd_list, t_shell *shell)
{
	int		exit_status;
	t_cmd	*current;

	exit_status = 0;
	current = cmd_list;
	if (!cmd_list || !shell)
		return (-1);
	setup_signals(EXECUTION_MODE);
	while (current)
	{
		if (current->next)
			exit_status = execute_single_cmd(current, shell);
		else
			exit_status = execute_single_cmd(current, shell);
		current = current->next;
	}
	shell->exit_status = exit_status;
	setup_signals(INTERACTIVE_MODE);
	clear_signal_received();
	return (exit_status);
}

int	execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;
	int	saved_stdin;
	int	saved_stdout;

	if (!cmd || !shell)
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (setup_redirections(cmd) != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (1);
	}
	if (is_builtin_cmd(cmd, shell))
		exit_status = execute_builtin_cmd(cmd, shell);
	else
		exit_status = execute_external_cmd(cmd, shell);
	restore_std_fds(saved_stdin, saved_stdout);
	cleanup_redirections(cmd);
	return (exit_status);
}
