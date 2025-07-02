/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:08 by rzt               #+#    #+#             */
/*   Updated: 2025/07/02 13:32:35 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
	// ft_putstr_fd("exit\n", STDERR_FILENO);

int	mini_exit_builtin(char **args, t_shell *shell)
{
	int	exit_code;

	exit_code = shell->exit_status;
	if (args[1])
	{
		if (!ft_isnbr(args[1]))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			cleanup_shell(shell);
			exit(2);
		}
		if (args[2])
		{
			ft_putstr_fd("minishell: too many arguments\n",
				STDERR_FILENO);
			return (1);
		}
		exit_code = ft_atoi(args[1]);
	}
	cleanup_shell(shell);
	exit((unsigned char)exit_code);
}
