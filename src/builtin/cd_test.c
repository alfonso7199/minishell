/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:08:03 by rzt               #+#    #+#             */
/*   Updated: 2025/06/09 19:39:26 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_pwd_vars(t_env *env_lst, char *str)
{
	char	*pwd_value;
	char	*oldpwd_value;

	printf("\t %s \n", str);
	pwd_value = get_env_value(env_lst, "PWD");
	oldpwd_value = get_env_value(env_lst, "OLDPWD");
	if (pwd_value)
		printf("PWD: %s\n\n", pwd_value);
	else
		printf("PWD: (not set)\n\n");
	if (oldpwd_value)
		printf("OLDPWD: %s\n\n", oldpwd_value);
	else
		printf("OLDPWD: (not set)\n\n");
}

void	print_current_directory(void)
{
	char	*current_directory;

	current_directory = getcwd(NULL, 0);
	if (current_directory)
		printf("Current directory: %s\n", current_directory);
	else
		printf("Current directory: Error!\n");
	free(current_directory);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	int		result;
	int		idx;

	(void)argc;
	idx = 1;
	env_list = mini_env(envp);
	print_current_directory();
	print_pwd_vars(env_list, "BEFORE mini_cd");
	if (argv[1])
	{
		while (argv[idx])
		{
			printf("%s", argv[idx]);
			idx++;
		}
	}
	else
		printf("(No arguments - go to HOME)\n\n");
	result = mini_cd(argv, &env_list);
	print_current_directory();
	print_pwd_vars(env_list, "After mini_cd");
	free_env_list(env_list);
	return (result);
}

/* 
clang src/builtin/cd.c src/builtin/cd_test.c src/builtin/env.c \
src/builtin/env2.c src/builtin/env3.c -Iinclude/ -Llibft/ -lft
*/