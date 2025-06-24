/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:42:56 by rzt               #+#    #+#             */
/*   Updated: 2025/06/24 17:27:39 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_commands(t_cmd *cmd_list, t_shell *shell)
{
	t_cmd	*current;
	int		exit_status;

	if (!cmd_list || !shell)
		return (-1);
	current = cmd_list;
	exit_status = 0;
	setup_signals(EXECUTION_MODE);
	while (current)
	{
		if (current->next)
			exit_status = execute_pipeline(current, shell);
		else
			exit_status = execute_single_cmd(current, shell);
		if (exit_status != 0)
			break ;
		current = current->next;
	}
	setup_signals(INTERACTIVE_MODE);
	return (exit_status);
}

int	execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	if (!cmd || !shell)
		return (1);
	if (setup_redirections(cmd) != 0)
		return (1);
	if (is_builtin_cmd(cmd, shell))
		exit_status = execute_builtin_cmd(cmd, shell);
	else
		exit_status = execute_external_cmd(cmd, shell);
	cleanup_redirections(cmd);
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
	return (1);
}
