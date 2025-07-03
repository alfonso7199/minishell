/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	restore_terminal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag |= (ECHO | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

int	handle_input_signal(char **full_input, char *input)
{
	(void)input;
	if (get_signal_received() == SIGINT)
	{
		clear_signal_received();
		if ((*full_input)[0] != '\0')
		{
			free(*full_input);
			*full_input = ft_strdup("");
		}
		return (-1);
	}
	return (0);
}

int	concatenate_input(char **full_input, char *input)
{
	char	*temp;

	if (*input)
		add_history(input);
	temp = *full_input;
	*full_input = ft_strjoin(*full_input, input);
	free(temp);
	free(input);
	return (0);
}

void	restore_terminal_after_command(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag |= (ECHO | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	is_empty_tokens(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == TOKEN_EOF)
		return (1);
	if (!tokens->value || tokens->value[0] == '\0')
		return (1);
	return (0);
}
