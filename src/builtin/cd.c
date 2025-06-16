/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:38 by rzt               #+#    #+#             */
/*   Updated: 2025/06/16 12:34:39 by rzamolo-         ###   ########.fr       */
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

static char	*get_target_path(char **args, t_env *envp)
{
	char	*home_path;

	if (!args[1])
	{
		home_path = get_env_value(envp, "HOME");
		if (!home_path)
		{
			ft_putstr_fd("minishel: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		ft_putstr_fd(home_path, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (ft_strdup(home_path));
	}
	return (ft_strdup(args[1]));
}

int	mini_cd(char **args, t_env **envp)
{
	char	*target_path;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	target_path = get_target_path(args, *envp);
	if (!target_path)
	{
		free(old_pwd);
		return (1);
	}
	if (chdir(target_path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(target_path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directorry\n", STDERR_FILENO);
		free(target_path);
		free(old_pwd);
		return (1);
	}
	update_pwd_vars(envp, old_pwd);
	free(target_path);
	free(old_pwd);
	return (0);
}
