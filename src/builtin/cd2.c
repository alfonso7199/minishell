/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:37:59 by rzt               #+#    #+#             */
/*   Updated: 2025/06/26 19:40:43 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_getcwd_error(void)
{
	ft_putstr_fd("minishell: cd: error retrieving current directory\n", 
		STDERR_FILENO);
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