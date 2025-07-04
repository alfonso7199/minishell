/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:08 by rzt               #+#    #+#             */
/*   Updated: 2025/07/04 13:04:30 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	error_numeric(char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	cleanup_shell(shell);
	exit(2);
}

static long	parse_arg_value(char *s)
{
	long	nbr;
	int		sign;
	int		i;
	int		digit;

	nbr = 0;
	sign = 1;
	i = 0;
	if (s[0] == '-' || s[0] == '+')
	{
		if (s[0] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		digit = s[i] - '0';
		nbr = nbr * 10 + digit;
		i++;
	}
	return (nbr * sign);
}

int	mini_exit(t_cmd *cmd, t_shell *shell)
{
	long	exit_code;

	if (cmd->args[1] && !ft_isnbr(cmd->args[1]))
		error_numeric(cmd->args[1], shell);
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (cmd->args[1])
		exit_code = parse_arg_value(cmd->args[1]);
	else
		exit_code = shell->exit_status;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	cleanup_shell(shell);
	exit((unsigned char)exit_code);
}
