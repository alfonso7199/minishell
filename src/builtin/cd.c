/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:38 by rzt               #+#    #+#             */
/*   Updated: 2025/06/30 09:47:35 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	update_pwd_vars(t_env **envp, char *old_pwd)
// {
// 	char	*current_pwd;

// 	current_pwd = getcwd(NULL, 0);
// 	if (!current_pwd)
// 		return ;
// 	if (old_pwd)
// 		set_env_value(envp, "OLDPWD", old_pwd);
// 	set_env_value(envp, "PWD", current_pwd);
// 	free(current_pwd);
// }

// static char	*get_home_path(t_env *envp)
// {
// 	char	*home_path;

// 	home_path = get_env_value(envp, "HOME");
// 	if (!home_path)
// 	{
// 		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
// 		return (NULL);
// 	}
// 	return (ft_strdup(home_path));
// }

// static char	*get_oldpwd_path(t_env *envp)
// {
// 	char	*oldpwd_path;

// 	oldpwd_path = get_env_value(envp, "OLDPWD");
// 	if (!oldpwd_path)
// 	{
// 		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
// 		return (NULL);
// 	}
// 	ft_putstr_fd(oldpwd_path, STDOUT_FILENO);
// 	ft_putstr_fd("\n", STDOUT_FILENO);
// 	return (ft_strdup(oldpwd_path));
// }

// static char	*get_target_path(char **args, t_env *envp)
// {
// 	if (!args[1])
// 		return (get_home_path(envp));
// 	if (ft_strncmp(args[1], "-", 2) == 0)
// 		return (get_oldpwd_path(envp));
// 	return (ft_strdup(args[1]));
// }

int	cd_error(int exitCode, char *msg)
{
	(void)exitCode;

	if (msg == NULL)
		ft_putstr_fd("minishell: cd: none or too many arguments\n",
			STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	return (1);
}

int	update_env(t_env **envp, char *env_var, char *value)
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

int	mini_cd(t_cmd *cmd, t_env **envp)
{
	char	*cwd;
	int		length;

	length = 0;
	while (cmd->args && cmd->args[length])
		length++;
	if (length > 2)
		return (cd_error(1, NULL));
	cwd = getcwd(NULL, 0);
	if (chdir(cmd->args[1]) < 0)
	{
		free(cwd);
		return (cd_error(1, cmd->args[1]));
	}
	if (find_env_node(*envp, "OLDPWD") != NULL && cwd != NULL)
		update_env(envp, "OLDPWD", cwd);
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (find_env_node(*envp, "PWD") != NULL && cwd != NULL)
		update_env(envp, "PWD", cwd);
	free(cwd);
	return (0);
}
