/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2025/06/26 17:55:15 by rzt              ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env				*env;
	int					exit_status;
	t_cmd				*cmd_list;
}	t_shell;

typedef enum e_signal_mode
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

/* Functiones helpers tokenizer */
void			handle_quoted_word(char *input, int *i, int *start,\
	t_quote_state *quote_type);
void			handle_unquoted_word(char *input, int *i);

/* Funciones del parser */
t_cmd			*parser(t_token *tokens);
t_cmd			*create_cmd(void);
t_redir			*create_redir(t_token_type type, char *file);
bool			is_redirection_token(t_token_type type);
bool			validate_syntax(t_token *tokens);

/* Funciones auxiliares del parser */
t_token			*process_command_token(t_cmd **cmd_list, t_token *token);

/* Funciones de utilidad del parser */
void			add_redir_to_cmd(t_cmd *cmd, t_redir *redir);
int				count_args(t_token *tokens);
t_token			*handle_redirection(t_token *tokens, t_cmd *cmd);
void			add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd);
t_token			*parse_args(t_token *tokens, t_cmd *cmd);
t_token			*fill_args(t_token *tokens, t_cmd *cmd);

/* Funciones de memoria del parser */
void			free_redirections(t_redir *redir);
void			free_args(char **args);
void			free_cmd_list(t_cmd *cmd_list);

/* **************** */
/* Builtin Commands */
/* **************** */
void			free_env_list(t_env *env_list);
/* echo */
int				mini_echo(char *arg[]);
/* exit */
void			mini_exit(char *arg[]);
int				mini_exit_builtin(char **args, t_shell *shell);
/* pwd */
int				mini_pwd(int fd);
/* export */
int				mini_export(char **args, t_env **envp);
/* unset */
int				mini_unset(char **args, t_env **envp);
/* cd */
int				mini_cd(char **args, t_env **envp);
/* env */
t_env			*find_env_node(t_env *envp, char *key);
void			set_env_value(t_env **envp, char *key, char *value);
int				count_env_vars(t_env *envp);
char			*create_env_string(char *key, char *value);
/* env2 */
int				env_key_match(char *env_key, char *search_key);
t_env			*create_env_node(char *key, char *value);
void			add_to_end(t_env **head, t_env *new_node);
void			add_env_node(t_env **head, char *key, char *value);
char			*get_env_value(t_env *envp, char *key);
/* env3 */
void			free_partial_array(char **array, int count);
void			free_env_list(t_env *env_list);
void			process_env_entry(char *env_str, t_env **env_lst);
t_env			*mini_env(char **envp);
int				mini_env_print(t_env *envp);

/* **************** */
/*      Signals     */
/* **************** */
/* signals */
void			setup_signals(t_signal_mode mode);
void			setup_execution_signals(void);
void			set_signal_received(sig_atomic_t sig);
sig_atomic_t	get_signal_received(void);
void			clear_signal_received(void);
/* signals - interactive */
void			setup_interactive_signals(void);
void			handle_interactive_sigint(int sig);
void			handle_interactive_sigquit(int sig);
/* signals - execution */
void			handle_execution_sigint(int sig);
void			handle_execution_sigquit(int sig);
void			handle_child_signals(void);
/* signals - heredoc */
void			setup_heredoc_signals(void);
void			handle_heredoc_sigint(int sig);
void			restore_heredoc_signals(void);
/* signals - reset */
void			reset_signal_state(void);
void			restore_default_signals(void);
void			ignore_all_signals(void);

/* **************** */
/*      Executor    */
/* **************** */
/* executor_main.c */
int				execute_commands(t_cmd *cmd_list, t_shell *shell);
int				execute_single_cmd(t_cmd *cmd, t_shell *shell);
int				is_builtin_cmd(t_cmd *cmd, t_shell *shell);
int				execute_builtin_cmd(t_cmd *cmd, t_shell *shell);

/* executor_external.c */
int				execute_external_cmd(t_cmd *cmd, t_shell *shell);
char			*find_command_path(char *cmd_name, t_env *env);
char			*check_absolute_path(char *path);
char			*search_in_paths(char *cmd_name, char **paths);
void			execute_child_process(t_cmd *cmd, char *cmd_path,\
	t_shell *shell);

/* executor_pipeline.c */
int				execute_pipeline(t_cmd *cmd_list, t_shell *shell);
int				count_commands(t_cmd *cmd_list);
int				**create_pipes(int pipe_count);
int				execute_pipeline_commands(t_cmd *cmd_list, t_shell *shell,\
	int **pipes, pid_t *pids);
void			execute_pipeline_child(t_cmd *cmd, t_shell *shell,\
	int **pipes, int cmd_index);

/* executor_redirections.c */
int				setup_redirections(t_cmd *cmd);
int				handle_single_redirection(t_redir *redir);
int				setup_input_redirection(t_redir *redir);
int				setup_output_redirection(t_redir *redir);
int				setup_append_redirection(t_redir *redir);

/* executor_utils.c */
int				wait_for_child(pid_t pid, int *status);
int				handle_command_not_found(char *cmd_name);
int				handle_fork_error(void);
void			print_file_error(char *filename, char *error_msg);
void			free_string_array(char **array);

/* executor_heredoc.c */
int				setup_heredoc_redirection(t_redir *redir);
void			heredoc_child_process(char *delimiter, int pipe_fd[2]);
int				setup_heredoc_input(int read_fd);
void			cleanup_redirections(t_cmd *cmd);
char			**convert_env_to_array(t_env *env_list);

/* executor_pipeline_utils.c */
void			setup_pipeline_redirections(int **pipes, int cmd_index,\
	int pipe_count);
void			close_all_pipes(int **pipes, int pipe_count);
int				wait_for_pipeline(pid_t *pids, int cmd_count);
int				get_exit_status(int status);
void			cleanup_pipeline(int **pipes, pid_t *pids, int pipe_count);

/* executor_cleanup.c */
int				**cleanup_partial_pipes(int **pipes, int count);
int				cleanup_pipes_error(int **pipes, int pipe_count);
void			free_partial_array(char **array, int count);
void			cleanup_shell(t_shell *shell);

/* Shell */
void			init_shell_values(t_shell *shell);
int				validate_shell_env(t_shell *shell);
t_shell			*init_shell(char **envp);
void			cleanup_shell(t_shell *shell);

/* Errores */
int				error_msg(char *msg);
// int     ft_error(int error, t_tools *tools);
// void    reset_tools(t_tools *tools);

/* Utils */
int				ft_isnbr(char *str);
#endif