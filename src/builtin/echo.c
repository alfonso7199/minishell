/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:39 by rzt               #+#    #+#             */
/*   Updated: 2025/06/04 19:43:24 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo(char *arg[])
{
	int	i;
	int	newline;
	
	i = 1;
	newline = 1;
	if (arg[i] && !ft_strncmp(arg[i], "-n", ft_strlen(arg[i])))
	{
		newline = 0;
		i++;
	}
	while (arg && arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
