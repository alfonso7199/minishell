/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/03 20:32:23 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	was_signal_received(void)
{
	return (get_signal_received() != 0);
}

int	update_exit_status_from_signal(int status)
{
	int	exit_code;

	exit_code = status;
	if (WIFSIGNALED(status))
	{
		exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			set_signal_received(SIGINT);
		else if (WTERMSIG(status) == SIGQUIT)
			set_signal_received(SIGQUIT);
	}
	return (exit_code);
}

void	setup_signals(t_signal_mode mode)
{
	if (mode == INTERACTIVE_MODE)
		setup_interactive_signals();
	else if (mode == EXECUTION_MODE)
		setup_execution_signals();
	else if (mode == HEREDOC_MODE)
		setup_heredoc_signals();
}

/* 
void	setup_execution_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT,  &sa, NULL) < 0)
		perror("sigaction SIGINT");
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		perror("sigaction SIGQUIT");
}
 */

void	setup_execution_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_execution_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) < 0)
		ft_putstr_fd("Error setting up SIGINT handler\n", STDERR_FILENO);
	sa_quit.sa_handler = handle_execution_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) < 0)
		ft_putstr_fd("Error setting up SIGQUIT handler\n", STDERR_FILENO);
}
