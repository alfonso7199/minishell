/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:08 by rzt               #+#    #+#             */
/*   Updated: 2025/06/26 12:19:22 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_exit(char *arg[])
{
	int	status_code;

	status_code = 0;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (arg[1])
	{
		if (!ft_isnbr(arg[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(arg[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(2);
		}
		if (arg[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", \
STDERR_FILENO);
			return ;
		}
		status_code = ft_atoi(arg[1]);
		exit((unsigned char)status_code);
	}
	exit(0);
}

int	mini_exit_builtin(char **args, t_shell *shell)
{
	int	exit_code;

	exit_code = shell->exit_status;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1])
	{
		if (!ft_isnbr(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			cleanup_shell(shell);
			exit(2);
		}
		if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			return (1);
		}
		exit_code = ft_atoi(args[1]);
	}
	cleanup_shell(shell);
	exit((unsigned char)exit_code);
}
