/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:30:00 by rzt               #+#    #+#             */
/*   Updated: 2025/06/27 14:30:00 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_commands(t_cmd *cmds)
{
	int		i;
	t_redir	*r;
	int		j;

	i = 0;
	while (cmds)
	{
		printf("Command %d:\n", ++i);
		printf("  Args: ");
		j = 0;
		while (cmds->args[j])
		{
			printf("%s ", cmds->args[j]);
			j++;
		}
		printf("\n");
		printf("  Redirections:\n");
		r = cmds->redirections;
		while (r)
		{
			printf("    Type: %d, File: %s\n", r->type, r->file);
			r = r->next;
		}
		cmds = cmds->next;
	}
}
