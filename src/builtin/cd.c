/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:38 by rzt               #+#    #+#             */
/*   Updated: 2025/07/04 12:25:22 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_env(t_env **envp, char *env_var, char *value)
{
	char	*export_comm;
	char	*aux;
	char	**command;
	int		status;

	export_comm = ft_strdup("export ");
	aux = ft_strjoin(export_comm, env_var);
	free(export_comm);
	export_comm = aux;
	aux = ft_strjoin(export_comm, "=");
	free(export_comm);
	export_comm = aux;
	aux = ft_strjoin(export_comm, value);
	free(export_comm);
	command = ft_split(aux, ' ');
	free(aux);
	if (command == NULL)
		return (error_msg("MALLOC ERROR"));
	status = mini_export(command, envp);
	free_split(command);
	return (status);
}

static int	get_cd_target(t_cmd *cmd, t_env **envp, char **target)
{
	if (!cmd->args[1])
	{
		*target = get_env_value(*envp, "HOME");
		if (!*target)
			return (error_msg("HOME no set"));
	}
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		*target = get_env_value(*envp, "OLDPWD");
		if (!*target)
			return (error_msg("OLDPWD not set"));
	}
	else if (cmd->args[1][0] == '$')
	{
		*target = get_env_value(*envp, cmd->args[1] + 1);
		if (!*target)
			return (cd_error(1, cmd->args[1]));
	}
	else
		*target = cmd->args[1];
	return (0);
}

static void	update_cd_env(t_env **envp, char *oldpwd)
{
	char	*cwd;

	if (oldpwd)
		update_env(envp, "OLDPWD", oldpwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env(envp, "PWD", cwd);
		free(cwd);
	}
}

static void	print_pwd_if_hifen(t_cmd *cmd)
{
	char	*cwd;

	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			ft_putstr_fd(cwd, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			free(cwd);
		}
	}
}

int	mini_cd(t_cmd *cmd, t_env **envp)
{
	char	*cwd;
	char	*target;
	int		length;
	int		ret;

	length = 0;
	while (cmd->args && cmd->args[length])
		length++;
	if (length > 2)
		return (cd_error(1, NULL));
	target = NULL;
	ret = get_cd_target(cmd, envp, &target);
	if (ret != 0)
		return (1);
	cwd = getcwd(NULL, 0);
	if (chdir(target) < 0)
	{
		free(cwd);
		return (cd_error(1, target));
	}
	update_cd_env(envp, cwd);
	free(cwd);
	print_pwd_if_hifen(cmd);
	return (0);
}
