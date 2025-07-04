/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:02:38 by rzt               #+#    #+#             */
/*   Updated: 2025/07/04 12:10:02 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*validate_absolute_path(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
		return (NULL);
	if (stat(path, &path_stat) != 0)
		return (NULL);
	if (!S_ISREG(path_stat.st_mode))
		return (NULL);
	if (access(path, X_OK) != 0)
		return (NULL);
	return (ft_strdup(path));
}

static char	*find_in_path_dirs(char *cmd_name, char **paths)
{
	int		i;
	char	*temp_path;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		if (!temp_path)
			return (NULL);
		full_path = ft_strjoin(temp_path, cmd_name);
		free(temp_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd_name, t_env *envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	if (!cmd_name)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (validate_absolute_path(cmd_name));
	path_env = get_env_value(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = find_in_path_dirs(cmd_name, paths);
	free_string_array(paths);
	return (full_path);
}

int	execute_external_cmd(t_cmd *cmd, t_shell *shell)
{
	struct stat	st;
	char		*cmd_path;
	pid_t		pid;
	int			status;

	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], F_OK) != 0)
			return (print_file_error(cmd->args[0],
					"No such file or directory"), 127);
		if (stat(cmd->args[0], &st) == 0 && S_ISDIR(st.st_mode))
			return (print_file_error(cmd->args[0], "Is a directory"), 126);
		if (access(cmd->args[0], X_OK) != 0)
			return (print_file_error(cmd->args[0], "Permission denied"), 126);
	}
	cmd_path = get_command_path(cmd->args[0], shell->env);
	if (!cmd_path)
		return (handle_command_not_found(cmd->args[0]));
	pid = fork();
	if (pid == -1)
		return (free(cmd_path), handle_fork_error());
	if (pid == 0)
		execute_child_process(cmd, cmd_path, shell);
	return (free(cmd_path), wait_for_child(pid, &status));
}

void	execute_child_process(t_cmd *cmd, char *cmd_path, t_shell *shell)
{
	char	**envp;

	handle_child_signals();
	envp = convert_env_to_array(shell->env);
	if (!envp)
		exit (1);
	if (execve(cmd_path, cmd->args, envp) == -1)
	{
		free_string_array(envp);
		free(cmd_path);
		exit (127);
	}
}
