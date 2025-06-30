/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:37:59 by rzt               #+#    #+#             */
/*   Updated: 2025/06/30 10:54:08 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	handle_chdir_error(char *target_path, char *old_pwd)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(target_path, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	free(target_path);
	free(old_pwd);
	return (1);
}