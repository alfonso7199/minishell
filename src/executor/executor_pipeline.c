/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:38:27 by rzt               #+#    #+#             */
/*   Updated: 2025/07/04 12:24:35 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_commands(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static int	**create_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * pipe_count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
			return (cleanup_partial_pipes(pipes, i));
		i++;
	}
	return (pipes);
}

static void	execute_pipeline_child(t_cmd *cmd, t_shell *shell, t_pipeinfo *info)
{
	char	*cmd_path;

	handle_child_signals();
	setup_pipeline_redirections(info->pipes, info->cmd_index, info->pipe_count);
	close_all_pipes(info->pipes, info->pipe_count);
	if (setup_redirections(cmd) != 0)
		exit(1);
	if (is_builtin_cmd(cmd, shell))
		exit(execute_builtin_cmd(cmd, shell));
	else
	{
		cmd_path = get_command_path(cmd->args[0], shell->env);
		if (!cmd_path)
		{
			handle_command_not_found(cmd->args[0]);
			exit(127);
		}
		execute_child_process(cmd, cmd_path, shell);
	}
}

static int	execute_pipeline_commands(t_cmd *cmd_list, t_shell *shell,
	int **pipes, pid_t *pids)
{
	t_cmd		*current;
	int			cmd_index;
	int			pipe_count;
	t_pipeinfo	info;

	current = cmd_list;
	cmd_index = 0;
	pipe_count = count_commands(cmd_list) - 1;
	while (current)
	{
		pids[cmd_index] = fork();
		if (pids[cmd_index] == -1)
			return (handle_fork_error());
		if (pids[cmd_index] == 0)
		{
			info.pipes = pipes;
			info.cmd_index = cmd_index;
			info.pipe_count = pipe_count;
			execute_pipeline_child(current, shell, &info);
		}
		current = current->next;
		cmd_index++;
	}
	close_all_pipes(pipes, pipe_count);
	return (wait_for_pipeline(pids, cmd_index));
}

int	execute_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	int		pipe_count;
	int		**pipes;
	pid_t	*pids;
	int		exit_status;

	pipe_count = count_commands(cmd_list) - 1;
	if (pipe_count <= 0)
		return (execute_single_cmd(cmd_list, shell));
	pipes = create_pipes(pipe_count);
	if (!pipes)
		return (1);
	pids = malloc(sizeof(pid_t) * (pipe_count + 1));
	if (!pids)
		return (cleanup_pipes_error(pipes, pipe_count));
	exit_status = execute_pipeline_commands(cmd_list, shell, pipes, pids);
	cleanup_pipeline(pipes, pids, pipe_count);
	return (exit_status);
}
