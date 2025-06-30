/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:38:39 by rzt               #+#    #+#             */
/*   Updated: 2025/06/26 17:49:47 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_with_escapes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
}

static int	check_flag(char *arg)
{
	int	i;

	i = 0;
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	mini_echo(char *arg[])
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (arg[i] && check_flag(arg[i]))
	{
		newline = 0;
		i++;
	}
	while (arg && arg[i])
	{
		print_with_escapes(arg[i]);
		if (arg[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
