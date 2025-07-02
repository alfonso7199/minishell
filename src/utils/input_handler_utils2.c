/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:00:00 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/15 10:00:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	check_and_free_empty_tokens(t_token *tokens, char *full_input)
{
	if (is_empty_tokens(tokens))
	{
		free(full_input);
		return (1);
	}
	return (0);
}

t_token	*expand_and_check_tokens(t_token *tokens, char *full_input)
{
	tokens = expand_tokens(tokens, NULL);
	if (is_empty_tokens(tokens))
	{
		free_tokens(tokens);
		free(full_input);
		return (NULL);
	}
	return (tokens);
}

int	execute_and_cleanup_cmds(t_cmd *cmds, t_shell *shell, char *full_input)
{
	if (!cmds)
	{
		write(2, "minishell: syntax error\n", 24);
		free(full_input);
		return (0);
	}
	execute_commands(cmds, shell);
	free_cmd_list(cmds);
	free(full_input);
	set_secondary_prompt(0);
	return (1);
}
