/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:36 by rzt               #+#    #+#             */
/*   Updated: 2025/06/05 12:17:10 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(NULL, 0);
	if (buff)
	{
		ft_putstr_fd(buff, STDOUT_FILENO);
		free(buff);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	else
		perror("pwd");
	return (1);
}
