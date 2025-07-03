/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:15 by rzt               #+#    #+#             */
/*   Updated: 2025/07/03 20:33:41 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_execution_sigint(int sig)
{
	(void)sig;
	set_signal_received(SIGINT);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	handle_execution_sigquit(int sig)
{
	(void)sig;
	set_signal_received(SIGQUIT);
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
