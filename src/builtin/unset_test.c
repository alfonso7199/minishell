/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:59:53 by rzt               #+#    #+#             */
/*   Updated: 2025/06/10 13:12:48 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	t_env	*tmp;
	int		result;

	(void)argc;
	env_list = mini_env(envp);
	printf("Before unset: \n");
	tmp = env_list;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	result = mini_unset(argv, &env_list);
	printf("After unset: \n");
	tmp = env_list;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	free_env_list(env_list);
	return (result);
}
