/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:03:49 by rzt               #+#    #+#             */
/*   Updated: 2025/06/05 20:20:40 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*dup_env;
	t_env	*tmp;
	
	(void)argc;
	(void)argv;
	dup_env = mini_env(envp);
	tmp = dup_env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	free_env_list(dup_env);
	return (0);
}
