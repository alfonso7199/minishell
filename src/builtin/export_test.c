/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:12:51 by rzt               #+#    #+#             */
/*   Updated: 2025/06/10 12:19:23 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	int		result;

	(void)argc;
	env_list = mini_env(envp);
	result = mini_export(argv, &env_list);
	free_env_list(env_list);
	return (result);
}
