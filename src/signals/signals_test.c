/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:44:16 by rzt               #+#    #+#             */
/*   Updated: 2025/06/11 12:52:50 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	test_interactive_mode(void)
{
	setup_signals(INTERACTIVE_MODE);
	reset_signal_state();
	printf("\nPress Ctrl+C (must show a new line and a prompt)\n");
	printf("minishell - signals> ");
	fflush(stdout);
	sleep(10);
	printf("\nEnd interactive mode test\n");
}

void	test_execution_mode(void)
{
	pid_t	pid;

	setup_signals(EXECUTION_MODE);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		handle_child_signals();
		execlp("sleep", "sleep", "10", NULL);
		exit(1);
	}
	wait(NULL);
	printf("\nEnd execution mode test\n");
}

void	test_heredoc(void)
{
	char	buffer[1024];
	ssize_t	bytes;

	setup_signals(HEREDOC_MODE);
	reset_signal_state();
	bytes = read(STDIN_FILENO, buffer, 1023);
	if (bytes == -1)
		perror("read");
	else
	{
		buffer[bytes] = '\0';
		printf("You typed: %s\n", buffer);
	}
	restore_heredoc_signals();	
}

int	main(void)
{
	test_interactive_mode();
	test_execution_mode();
	test_heredoc();
	return (0);
}