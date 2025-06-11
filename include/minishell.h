/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2025/06/11 12:40:07 by rzt              ###   ########.fr       */
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

/* Global  */
extern volatile sig_atomic_t g_signal_received;

/* Estados del lexer para manejo de comillas */
typedef enum e_quote_state
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_state;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_EXIT_STATUS,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	bool				quoted;
	t_quote_state		quote_type;
	struct s_token		*next;
}	t_token;

typedef struct s_redir
{
	t_token_type		type;
	char				*file;
	int					fd;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd {
    char            **args;
    t_redir         *redirections;
    struct s_cmd    *next;
} t_cmd;

typedef struct s_shell
{
	char				**env;
	int					exit_status;
	t_cmd				*cmd_list;
}	t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct	s_env	*next;
}	t_env;

typedef enum	e_signal_mode
{
	INTERACTIVE_MODE,
	EXECUTION_MODE,
	HEREDOC_MODE
}	t_signal_mode;

/* Funciones del tokenizer */
bool			is_special_char(char c);
bool			is_quote(char c);
t_token			*tokenizer(char *input);
t_token			*create_token(t_token_type type, char *value, bool quoted,
					t_quote_state quote_type);
void			free_tokens(t_token *tokens);

/* Funciones de utilidad del tokenizer */
void			add_token_to_list(t_token **tokens, t_token *new_token);
t_token_type	get_token_type(char *str);
void			skip_whitespace(char *input, int *i);
t_token			*get_next_token(char *input, int *i);
t_token			*process_env_var(char *input, int *i);

/* Funciones de extracción del tokenizer */
char			*extract_word(char *input, int *i, t_quote_state *quote_type,
					bool *quoted);
char			*extract_operator(char *input, int *i);
char			*extract_env_var(char *input, int *i);
t_token			*process_operator(char *input, int *i);
t_token			*process_word(char *input, int *i);

/* **************** */
/* Builtin Commands */
/* **************** */
void	free_env_list(t_env *env_list);
int     mini_echo(char *arg[]);
void	mini_exit(char *arg[]);
int 	mini_pwd(int fd);
/* env */
t_env	*find_env_node(t_env *envp, char *key);
void	set_env_value(t_env **envp, char *key, char *value);
int		count_env_vars(t_env *envp);
char	*create_env_string(char *key, char *value);
/* env2 */
int		env_key_match(char *env_key, char *search_key);
t_env	*create_env_node(char *key, char *value);
void	add_to_end(t_env **head, t_env *new_node);
void	add_env_node(t_env **head, char *key, char *value);
char	*get_env_value(t_env *envp, char *key);
/* env3 */
void	free_partial_array(char **array, int count);
void	free_env_list(t_env *env_list);
void	process_env_entry(char *env_str, t_env **env_lst);
t_env	*mini_env(char **envp);
/* export */
int		is_valid_identifier(char *str);
void	print_export_error(char *arg);
void	print_sorted_env(t_env *envp);
int		process_export_arg(char *arg, t_env **envp);
int		mini_export(char **args, t_env **envp);
/* unset */
int		is_valid_unset_identifier(char *str);
void	print_unset_error(char *arg);
void	remove_env_node(t_env **envp, char *key);
int		mini_unset(char **args, t_env **envp);
/* cd */
void	update_pwd_vars(t_env **envp, char *old_pwd);
char	*get_target_path(char **args, t_env *envp);
int		mini_cd(char **args, t_env **envp);

/* **************** */
/*      Signals     */
/* **************** */
/* signals */
void	setup_signals(t_signal_mode mode);
void	setup_execution_signals(void);
/* signals - interactive */
void	setup_interactive_signals(void);
void	handle_interactive_sigint(int sig);
void	handle_interactive_sigquit(int sig);
/* signals - execution */
void	handle_execution_sigint(int sig);
void	handle_execution_sigquit(int sig);
void	handle_child_signals(void);
/* signals - heredoc */
void	setup_heredoc_signals(void);
void	handle_heredoc_sigint(int sig);
void	restore_heredoc_signals(void);
/* signals - reset */
void	reset_signal_state(void);
void	restore_default_signals(void);
void	ignore_all_signals(void);

/* Errores */
int     error_msg(char *msg);
// int     ft_error(int error, t_tools *tools);
// void    reset_tools(t_tools *tools);

#endif