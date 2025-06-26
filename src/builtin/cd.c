/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:38 by rzt               #+#    #+#             */
/*   Updated: 2025/06/26 19:42:53 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_pwd_vars(t_env **envp, char *old_pwd)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return ;
	if (old_pwd)
		set_env_value(envp, "OLDPWD", old_pwd);
	set_env_value(envp, "PWD", current_pwd);
	free(current_pwd);
}

static char	*get_home_path(t_env *envp)
{
	char	*home_path;

	home_path = get_env_value(envp, "HOME");
	if (!home_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (ft_strdup(home_path));
}

static char	*get_oldpwd_path(t_env *envp)
{
	char	*oldpwd_path;

	oldpwd_path = get_env_value(envp, "OLDPWD");
	if (!oldpwd_path)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (NULL);
	}
	ft_putstr_fd(oldpwd_path, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (ft_strdup(oldpwd_path));
}

static char	*get_target_path(char **args, t_env *envp)
{
	if (!args[1])
		return (get_home_path(envp));
	if (ft_strncmp(args[1], "-", 2) == 0)
		return (get_oldpwd_path(envp));
	return (ft_strdup(args[1]));
}

int	mini_cd(char **args, t_env **envp)
{
	char	*target_path;
	char	*old_pwd;
	int		ret;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (handle_getcwd_error());
	target_path = get_target_path(args, *envp);
	if (!target_path)
	{
		free(old_pwd);
		return (1);
	}
	ret = chdir(target_path);
	if (ret == -1)
		return (handle_chdir_error(target_path, old_pwd));
	update_pwd_vars(envp, old_pwd);
	free(target_path);
	free(old_pwd);
	return (0);
}
