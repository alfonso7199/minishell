/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:43:06 by rzt               #+#    #+#             */
/*   Updated: 2025/07/02 17:27:28 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_builtin_cmd_extended(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen("echo")) == 0)
		return (mini_echo(cmd->args));
	if (ft_strncmp(cmd->args[0], "cd", ft_strlen("cd")) == 0)
		return (mini_cd(cmd, &shell->env));
	if (ft_strncmp(cmd->args[0], "pwd", ft_strlen("pwd")) == 0)
		return (mini_pwd(STDOUT_FILENO));
	if (ft_strncmp(cmd->args[0], "export", ft_strlen("export")) == 0)
		return (mini_export(cmd->args, &shell->env));
	if (ft_strncmp(cmd->args[0], "unset", ft_strlen("unset")) == 0)
		return (mini_unset(cmd->args, &shell->env));
	if (ft_strncmp(cmd->args[0], "env", ft_strlen("env")) == 0)
		return (mini_env_print(shell->env));
	if (ft_strncmp(cmd->args[0], "exit", ft_strlen("exit")) == 0)
		return (mini_exit(cmd, shell));
	return (1);
}

int	is_builtin_cmd_extended(t_cmd *cmd)
{
	char	*cmd_name;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	cmd_name = cmd->args[0];
	if (ft_strncmp(cmd_name, "echo", 5) == 0 && ft_strlen(cmd_name) == 4)
		return (1);
	if (ft_strncmp(cmd_name, "cd", 3) == 0 && ft_strlen(cmd_name) == 2)
		return (1);
	if (ft_strncmp(cmd_name, "pwd", 4) == 0 && ft_strlen(cmd_name) == 3)
		return (1);
	if (ft_strncmp(cmd_name, "export", 7) == 0 && ft_strlen(cmd_name) == 6)
		return (1);
	if (ft_strncmp(cmd_name, "unset", 6) == 0 && ft_strlen(cmd_name) == 5)
		return (1);
	if (ft_strncmp(cmd_name, "env", 4) == 0 && ft_strlen(cmd_name) == 3)
		return (1);
	if (ft_strncmp(cmd_name, "exit", 5) == 0 && ft_strlen(cmd_name) == 4)
		return (1);
	return (0);
}
