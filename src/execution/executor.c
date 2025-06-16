/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:42:56 by rzt               #+#    #+#             */
/*   Updated: 2025/06/16 12:09:47 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	size_t	cmd_len;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	cmd_len = ft_strlen(cmd->args[0]);
	return (!ft_strncmp(cmd->args[0], "cd", cmd_len) \
|| !ft_strncmp(cmd->args[0], "echo", cmd_len) \
|| !ft_strncmp(cmd->args[0], "env", cmd_len) \
|| !ft_strncmp(cmd->args[0], "exit", cmd_len) \
|| !ft_strncmp(cmd->args[0], "export", cmd_len) \
|| !ft_strncmp(cmd->args[0], "pwd", cmd_len) \
|| !ft_strncmp(cmd->args[0], "unset", cmd_len));
}

int	execute_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
		return (mini_cd(cmd));
	if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])))
		return (mini_echo(cmd));
	if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])))
		return (mini_env(cmd));
	if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
		return (mini_cd(cmd));
	if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])))
		return (mini_echo(cmd));
	if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])))
		return (mini_env(cmd));
	if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])))
		return (mini_unset(cmd));
}

int	execute_commands(t_cmd *cmd)
{
	t_cmd	*current_cmd;
	int		exit_status;

	current_cmd = cmd;
	exit_status = 0;
	while (current_cmd)
	{
		if (is_builtin(current_cmd))
			exit_status = execute_builtin(current_cmd);
		else
			printf("External command!\n");
	}
	return (exit_status);
}
