/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:03:49 by rzt               #+#    #+#             */
/*   Updated: 2025/06/05 17:44:16 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, const char *argv[], const char *envp[])
{
	t_env	*dup_env;
	t_env	*tmp;
	
	(void)argc;
	(void)argv;
	dup_env = env(envp);
	while (dup_env)
	{
		printf("%s=%s\n", dup_env->key, dup_env->value);
		tmp = dup_env->next;
		dup_env = tmp;
	}
	return (0);
}
