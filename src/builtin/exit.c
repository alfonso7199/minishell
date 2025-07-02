/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:08 by rzt               #+#    #+#             */
/*   Updated: 2025/07/02 17:28:08 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mini_exit(t_cmd *cmd, t_shell *shell)
{
	int		exit_code;

	exit_code = shell->exit_status;
	if (cmd->args[1])
	{
		if (!ft_isnbr(cmd->args[1]))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			cleanup_shell(shell);
			exit(2);
		}
		if (cmd->args[2])
		{
			ft_putstr_fd("minishell: too many arguments\n",
				STDERR_FILENO);
			return (1);
		}
		exit_code = ft_atoi(cmd->args[1]);
	}
	ft_putstr_fd("exit\n", STDIN_FILENO);
	cleanup_shell(shell);
	exit(exit_code & 0xFF);
}
