/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:30:28 by rzt               #+#    #+#             */
/*   Updated: 2025/06/12 23:12:06 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static volatile sig_atomic_t	g_signal_received = 0;

void	set_signal_received(sig_atomic_t sig)
{
	g_signal_received = sig;
}

sig_atomic_t	get_signal_received(void)
{
	return (g_signal_received);
}

void	clear_signal_received(void)
{
	g_signal_received = 0;
}
