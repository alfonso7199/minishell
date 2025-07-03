/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2025/06/27 09:14:07 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_signals_and_cleanup(int result, char *full_input)
{
	if (result == -1)
	{
		clear_signal_received();
		restore_terminal_after_command();
		setup_signals(INTERACTIVE_MODE);
		return (1);
	}
	if (result == 0)
	{
		free(full_input);
		return (0);
	}
	if (get_signal_received() == SIGINT)
	{
		clear_signal_received();
		restore_terminal_after_command();
		setup_signals(INTERACTIVE_MODE);
		return (1);
	}
	return (-42);
}

static int	init_minishell(t_shell **shell, char **envp)
{
	*shell = init_shell(envp);
	if (!*shell)
		return (0);
	setup_signals(INTERACTIVE_MODE);
	return (1);
}

static int	handle_loop_iteration(t_shell *shell)
{
	char	*full_input;
	t_token	*tokens;
	int		result;
	int		signal_status;

	full_input = ft_strdup("");
	result = handle_input_loop(&full_input, &tokens);
	if (result == 0)
	{
		free(full_input);
		return (0);
	}
	signal_status = handle_signals_and_cleanup(result, full_input);
	if (signal_status != -42)
	{
		free(full_input);
		return (1);
	}
	if (!process_command(tokens, shell, full_input))
	{
		restore_terminal_after_command();
		return (1);
	}
	restore_terminal_after_command();
	return (1);
}

static int	main_loop(t_shell *shell)
{
	while (1)
	{
		if (!handle_loop_iteration(shell))
			break ;
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	if (argc != 1 || argv[1])
		printf("This program does not accept arguments\n");
	if (!init_minishell(&shell, envp))
		return (1);
	main_loop(shell);
	cleanup_shell(shell);
	return (0);
}
