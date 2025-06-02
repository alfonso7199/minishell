/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <libgen.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define GREEN    "\033[32m"
# define RESET    "\033[0m"
# define RED      "\033[31m"

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
} t_token_type;

typedef struct s_token {
    t_token_type   type;
    char          *value;
    struct s_token *next;
} t_token;

typedef struct s_redir {
    t_token_type   type;
    char          *file;
    struct s_redir *next;
} t_redir;

typedef struct s_cmd {
    char         **args;
    t_redir      *redirections;
    struct s_cmd *next;
} t_cmd;

t_token *tokenizer(char *input);
t_cmd   *parser(t_token *tokens);


/* Errores */
int     error_msg(char *msg);
int     ft_error(int error, t_tools *tools);
void    reset_tools(t_tools *tools);

#endif