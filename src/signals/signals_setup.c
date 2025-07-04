/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/04 12:40:01 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_signals(t_signal_mode mode)
{
	if (mode == INTERACTIVE_MODE)
		setup_interactive_signals();
	else if (mode == EXECUTION_MODE)
		setup_execution_signals();
	else if (mode == HEREDOC_MODE)
		setup_heredoc_signals();
}
