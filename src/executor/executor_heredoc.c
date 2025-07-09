/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:51:26 by rzt               #+#    #+#             */
/*   Updated: 2025/07/09 12:41:32 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	heredoc_child_process(char *delimiter, int pipe_fd[2])
{
	char	*line;

	close(pipe_fd[0]);
	setup_signals(HEREDOC_MODE);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

static int	setup_heredoc_input(int read_fd)
{
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		close(read_fd);
		return (1);
	}
	close(read_fd);
	return (0);
}

void	cleanup_redirections(t_cmd *cmd)
{
	t_redir	*current;

	if (!cmd)
		return ;
	current = cmd->redirections;
	while (current)
	{
		if (current->fd != -1)
		{
			close(current->fd);
			current->fd = -1;
		}
		current = current->next;
	}
}

char	**convert_env_to_array(t_env *env_list)
{
	int		count;
	char	**env_array;
	t_env	*current;
	int		i;

	count = count_env_vars(env_list);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current && i < count)
	{
		env_array[i] = create_env_string(current->key, current->value);
		if (!env_array[i])
		{
			free_partial_array(env_array, i);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	setup_heredoc_redirection(t_redir *redir)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	if (pid == 0)
		heredoc_child_process(redir->file, pipe_fd);
	close(pipe_fd[1]);
	if (wait_for_child(pid, &status) != 0)
	{
		close(pipe_fd[0]);
		restore_terminal_after_command();
		return (1);
	}
	restore_terminal_after_command();
	return (setup_heredoc_input(pipe_fd[0]));
}
