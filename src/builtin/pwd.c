/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:36 by rzt               #+#    #+#             */
/*   Updated: 2025/06/05 20:20:04 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mini_pwd(int fd)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(NULL, 0);
	if (buff)
	{
		ft_putstr_fd(buff, fd);
		free(buff);
		ft_putstr_fd("\n", fd);
		return (0);
	}
	else
		perror("pwd");
	return (1);
}
