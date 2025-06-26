/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:42:56 by rzt               #+#    #+#             */
/*   Updated: 2025/06/26 12:00:10 by rzt              ###   ########.fr       */
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

	if (!cmd_list || !shell)
		return (-1);
	setup_signals(EXECUTION_MODE);
	if (cmd_list->next)
		exit_status = execute_pipeline(cmd_list, shell);
	else
		exit_status = execute_single_cmd(cmd_list, shell);
	shell->exit_status = exit_status;
	setup_signals(INTERACTIVE_MODE);
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
	cleanup_redirections(cmd);
	restore_std_fds(saved_stdin, saved_stdout);
	return (exit_status);
}

int	is_builtin_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_name;

	(void)shell;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	cmd_name = cmd->args[0];
	if (ft_strncmp(cmd_name, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "cd", ft_strlen("cd")) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "pwd", ft_strlen("pwd")) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "export", ft_strlen("export")) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "unset", ft_strlen("unset")) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "env", ft_strlen("env")) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}

int	execute_builtin_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen("echo")) == 0)
		return (mini_echo(cmd->args));
	if (ft_strncmp(cmd->args[0], "cd", ft_strlen("cd")) == 0)
		return (mini_cd(cmd->args, &shell->env));
	if (ft_strncmp(cmd->args[0], "pwd", ft_strlen("pwd")) == 0)
		return (mini_pwd(STDOUT_FILENO));
	if (ft_strncmp(cmd->args[0], "export", ft_strlen("export")) == 0)
		return (mini_export(cmd->args, &shell->env));
	if (ft_strncmp(cmd->args[0], "unset", ft_strlen("unset")) == 0)
		return (mini_unset(cmd->args, &shell->env));
	if (ft_strncmp(cmd->args[0], "env", ft_strlen("env")) == 0)
		return (mini_env_print(shell->env));
	if (ft_strncmp(cmd->args[0], "exit", ft_strlen("exit")) == 0)
		return (mini_exit_builtin(cmd->args, shell));
	return (1);
}
