/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:02:38 by rzt               #+#    #+#             */
/*   Updated: 2025/06/24 17:12:11 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_external_cmd(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	cmd_path = find_command_path(cmd->args[0], shell->env);
	if (!cmd_path)
		return (handle_command_not_found(cmd->args[0]));
	pid = fork();
	if (pid == -1)
		return (handle_fork_error());
	if (pid == 0)
		execute_child_process(cmd, cmd_path, shell);
	return (wait_for_child(pid, &status));
}

char	*find_command_path(char *cmd_name, t_env *envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	if (!cmd_name)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (check_absolute_path(cmd_name));
	path_env = get_env_value(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = search_in_paths(cmd_name, paths);
	free_string_array(paths);
	return (full_path);
}

char	*check_absolute_path(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISREG(path_stat.st_mode) && (path_stat.st_mode & S_IXUSR))
			return (path);
	}
	return (NULL);
}

char	*search_in_paths(char *cmd_name, char **paths)
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
