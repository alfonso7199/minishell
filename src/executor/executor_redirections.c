/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:35:37 by rzt               #+#    #+#             */
/*   Updated: 2025/07/04 12:20:22 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	setup_input_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		print_file_error(redir->file, "No such file or directory");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	redir->fd = fd;
	return (0);
}

static int	setup_output_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_file_error(redir->file, "Permission denied");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	redir->fd = fd;
	return (0);
}

static int	setup_append_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_file_error(redir->file, "Permission denied");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	redir->fd = fd;
	return (0);
}

static int	handle_single_redirection(t_redir *redir)
{
	if (!redir || !redir->file)
		return (1);
	if (redir->type == TOKEN_REDIR_IN)
		return (setup_input_redirection(redir));
	if (redir->type == TOKEN_REDIR_OUT)
		return (setup_output_redirection(redir));
	if (redir->type == TOKEN_APPEND)
		return (setup_append_redirection(redir));
	if (redir->type == TOKEN_HEREDOC)
		return (setup_heredoc_redirection(redir));
	return (1);
}

int	setup_redirections(t_cmd *cmd)
{
	t_redir	*current;
	int		result;

	if (!cmd)
		return (0);
	current = cmd->redirections;
	while (current)
	{
		result = handle_single_redirection(current);
		if (result != 0)
			return (result);
		current = current->next;
	}
	return (0);
}
