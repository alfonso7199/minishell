/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2025/07/04 12:48:21 by rzt              ###   ########.fr       */
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

# define SIGINT 2
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
	TOKEN_SEMICOLON,
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

typedef struct s_pipeline
{
	t_cmd					*cmds;
	struct s_pipeline		*next;
}	t_pipeline;

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

typedef struct s_pipeinfo
{
	int	**pipes;
	int	cmd_index;
	int	pipe_count;
}	t_pipeinfo;

typedef struct s_word_ctx
{
	int				start;
	char			*fragment;
	char			*result;
	t_quote_state	qt_tmp;
	bool			quoted_tmp;
	bool			only_single_quote;
	t_quote_state	*quote_type;
	bool			*quoted;
}	t_word_ctx;

/* shell.c */
t_shell			*init_shell(char **envp);
void			cleanup_shell(t_shell *shell);

/* SIGNALS */
/*  */
void			handle_child_signals(void); // signals_execution? 
/* signals_setup.c */
void			setup_signals(t_signal_mode mode);
/* signals_state.c */
void			set_signal_received(sig_atomic_t sig);
sig_atomic_t	get_signal_received(void);
void			clear_signal_received(void);
void			set_secondary_prompt(sig_atomic_t state);
sig_atomic_t	get_secondary_prompt(void);
/* signals_execution.c */
void			setup_execution_signals(void);
void			handle_execution_sigint(int sig);
void			handle_execution_sigquit(int sig);
/* signals_heredoc.c */
void			setup_heredoc_signals(void);
/* signals_interactive */
void			setup_interactive_signals(void);
void			setup_secondary_prompt_signals(void);
void			handle_interactive_sigint(int sig);

/* INPUT */
/* input_handler.c */
int				handle_input_loop(char **full_input, t_token **tokens);
int				process_command(t_token *tokens, t_shell *shell,
					char *full_input);
/* input_handler_utils.c */
int				handle_input_signal(char **full_input, char *input);
int				concatenate_input(char **full_input, char *input);
void			restore_terminal_after_command(void);
int				is_empty_tokens(t_token *tokens);
void			restore_terminal(void);
/* input_handler_utils2.c */
int				check_and_free_empty_tokens(t_token *tokens, char *full_input);
t_token			*expand_and_check_tokens(t_token *tokens, char *full_input);
int				expand_and_check_tokens_internal(t_token **tokens,
					t_shell *shell, char *full_input);
void			execute_all_pipelines(t_pipeline *pipelines, t_shell *shell);

/* TOKENIZER */
/* tokenizer.c */
t_token			*tokenizer(char *input);
void			free_tokens(t_token *tokens);
t_token			*create_token(t_token_type type, char *value, bool quoted,
					t_quote_state quote_type);
bool			is_special_char(char c);
bool			is_quote(char c);
/* tokenizer_utils.c */
void			skip_whitespace(char *input, int *i);
void			add_token_to_list(t_token **tokens, t_token *new_token);
t_token_type	get_token_type(char *str);
/* tokenizer_process.c */
t_token			*get_next_token(char *input, int *i);
/* tokenizer_extract.c */
char			*extract_operator(char *input, int *i);
char			*extract_word(char *input, int *i, t_quote_state *quote_type,
					bool *quoted);
char			*extract_quoted_word(char *input, int *i,
					t_quote_state *quote_type, bool *quoted);
/* tokenizer_extract_utils.c */
char			*extract_word_body(char *input, int *i,
					t_quote_state *quote_type, bool *quoted);
/* tokenizer_helpers.c */
bool			handle_quoted_word(char *input, int *i, int *start,
					t_quote_state *quote_type);
char			*process_escapes_in_quotes(char *str, t_quote_state quote_type);
void			handle_unquoted_word(char *input, int *i);

/* EXPANDER */
/* expand_vars.c */
t_token			*expand_tokens(t_token *tokens, t_shell *shell);
char			*expand_env_var(char *str, t_shell *shell);
char			*expand_variables_loop(char *str, t_shell *shell, char *result);
/* expand_utils.c */
char			*process_character(char *result, char c);
char			*handle_variable_expansion(char *str, int *i, char *result,
					t_shell *shell);
/* expand_utils2.c */
char			*expand_variables(char *str, t_shell *shell);
int				is_escaped_dollar(const char *str, int pos);
t_token			*remove_empty_token(t_token *tokens, t_token *prev,
					t_token **current);

/* PARSER */
/* parser.c */
t_redir			*create_redir(t_token_type type, char *file);
bool			validate_syntax_loop(t_token *current, bool *expect_word);
t_cmd			*create_cmd(void);
t_pipeline		*parser(t_token *tokens);
/* parser_memory.c */
void			free_cmd_list(t_cmd *cmd_list);
/* parser_utils.c */
t_token			*handle_redirection(t_token *tokens, t_cmd *cmd);
t_token			*parse_args(t_token *tokens, t_cmd *cmd);
/*  parser_utils2.c */
t_pipeline		*add_new_pipeline(t_pipeline **pipeline_list,
					t_pipeline **current_pipeline);
bool			add_new_cmd(t_pipeline *current_pipeline, t_cmd **current_cmd,
					t_token **current_token);
t_token			*fill_args(t_token *tokens, t_cmd *cmd);

/* parser_utils3.c */
bool			has_redirection_error(t_token *current);
bool			has_pipe_semicolon_error(t_token *current);
bool			is_redirection_token(t_token_type type);

/* EXECUTOR */
/* executor.c */
int				execute_commands(t_cmd *cmd_list, t_shell *shell);
int				execute_single_cmd(t_cmd *cmd, t_shell *shell);
/* executor_builtin.c */
int				is_builtin_cmd(t_cmd *cmd, t_shell *shell);
int				execute_builtin_cmd(t_cmd *cmd, t_shell *shell);
/* executor_cleanup.c */
int				**cleanup_partial_pipes(int **pipes, int count);
void			free_partial_array(char **array, int count);
/* executor_heredoc.c */
void			cleanup_redirections(t_cmd *cmd);
char			**convert_env_to_array(t_env *env_list);
int				setup_heredoc_redirection(t_redir *redir);
/* executor_external.c */
int				execute_external_cmd(t_cmd *cmd, t_shell *shell);
void			execute_child_process(t_cmd *cmd, char *cmd_path,
					t_shell *shell);
char			*get_command_path(char *cmd_name, t_env *envp);
/* executor_pipeline.c */
int				execute_pipeline(t_cmd *cmd_list, t_shell *shell);
/* executor_pipeline_utils.c */
void			close_all_pipes(int **pipes, int pipe_count);
int				wait_for_pipeline(pid_t	*pids, int cmd_count);
void			cleanup_pipeline(int **pipes, pid_t *pids, int pipe_count);
void			setup_pipeline_redirections(int **pipes, int cmd_index,
					int pipe_count);
/* executor_redirections.c */
int				setup_redirections(t_cmd *cmd);
/* executor_utils.c */
void			free_string_array(char **array);
int				wait_for_child(pid_t pid, int *status);
/* BUILTIN */
/* cd.c */
int				mini_cd(t_cmd *cmd, t_env **envp);
/* echo.c */
int				mini_echo(char *arg[]);
/* exit.c */
int				mini_exit(t_cmd *cmd, t_shell *shell);
/* export.c */
int				mini_export(char **args, t_env **envp);
void			print_sorted_env(t_env *envp);
/* pwd.c */
int				mini_pwd(int fd);
/* unset.c */
int				mini_unset(char **args, t_env **envp);
/* env.c */
t_env			*mini_env(char **envp);
void			sort_env_list(t_env *env);
int				mini_env_print(t_env *envp);
/* env2.c */
char			*get_env_value(t_env *envp, char *key);
void			add_env_node(t_env **head, char *key, char *value);
int				env_key_match(char *env_key, char *search_key);
/* env3.c */
char			*create_env_string(char *key, char *value);
int				count_env_vars(t_env *envp);
void			set_env_value(t_env **envp, char *key, char *value);
t_env			*find_env_node(t_env *envp, char *key);
void			free_env_list(t_env *env_list);
/* env4.c */
void			increment_shlvl(t_env **envp);

/* ERROR */
/* error.c */
int				error_msg(char *msg);
int				cleanup_pipes_error(int **pipes, int pipe_count);
void			print_file_error(char *filename, char *error_msg);
int				cd_error(int exitCode, char *msg);
/* handler_error.c */
int				handle_fork_error(void);
int				handle_command_not_found(char *cmd_name);

/* ft_isnbr */
int				ft_isnbr(char *str);
/* ft_strjoin_free.c */
char			*ft_strjoin_free(char *s1, const char *s2);
/* ft_free_split.c */
void			free_split(char **array);
char			*cut_whitespaces(char *str); // free_split?
#endif