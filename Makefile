# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 22:37:10 by rzt               #+#    #+#              #
#    Updated: 2025/07/04 12:04:50 by rzt              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
INCLUDE_DIR = ./include
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

SRC_DIR		= ./src

OBJ_DIR		= obj

LDFLAGS = -lreadline -lncurses -lhistory

SRC_FILES	= \
    $(SRC_DIR)/minishell.c \
	$(SRC_DIR)/shell.c \
	$(SRC_DIR)/tokenizing/tokenizer.c \
	$(SRC_DIR)/tokenizing/tokenizer_utils.c \
	$(SRC_DIR)/tokenizing/tokenizer_process.c \
	$(SRC_DIR)/tokenizing/tokenizer_helpers.c \
	$(SRC_DIR)/tokenizing/tokenizer_extract.c \
	$(SRC_DIR)/tokenizing/tokenizer_extract_utils.c \
	$(SRC_DIR)/signals/signals_setup.c \
	$(SRC_DIR)/signals/signals_execution.c \
	$(SRC_DIR)/signals/signals_interactive.c \
	$(SRC_DIR)/signals/signals_heredoc.c \
	$(SRC_DIR)/signals/signals_state.c \
	$(SRC_DIR)/parsing/parser.c \
	$(SRC_DIR)/parsing/parser_utils.c \
	$(SRC_DIR)/parsing/parser_utils2.c \
	$(SRC_DIR)/parsing/parser_memory.c \
	$(SRC_DIR)/parsing/expand_vars.c \
	$(SRC_DIR)/parsing/expand_utils.c \
	$(SRC_DIR)/parsing/expand_utils2.c \
	$(SRC_DIR)/parsing/parser_utils3.c \
	$(SRC_DIR)/builtin/echo.c \
	$(SRC_DIR)/builtin/pwd.c \
	$(SRC_DIR)/builtin/env.c \
	$(SRC_DIR)/builtin/env2.c \
	$(SRC_DIR)/builtin/env3.c \
	$(SRC_DIR)/builtin/env4.c \
	$(SRC_DIR)/builtin/exit.c \
	$(SRC_DIR)/builtin/unset.c \
	$(SRC_DIR)/builtin/export.c \
	$(SRC_DIR)/builtin/export2.c \
	$(SRC_DIR)/builtin/cd.c \
	$(SRC_DIR)/executor/executor.c \
	$(SRC_DIR)/executor/executor_cleanup.c \
	$(SRC_DIR)/executor/executor_builtin.c \
	$(SRC_DIR)/executor/executor_external.c \
	$(SRC_DIR)/executor/executor_heredoc.c \
	$(SRC_DIR)/executor/executor_pipeline.c \
	$(SRC_DIR)/executor/executor_pipeline_utils.c \
	$(SRC_DIR)/executor/executor_redirections.c \
	$(SRC_DIR)/executor/executor_utils.c \
	$(SRC_DIR)/utils/debug.c \
	$(SRC_DIR)/utils/ft_free_split.c \
	$(SRC_DIR)/utils/ft_isnbr.c \
	$(SRC_DIR)/utils/ft_strjoin_free.c \
	$(SRC_DIR)/utils/input_handler.c \
	$(SRC_DIR)/utils/input_handler_utils.c \
	$(SRC_DIR)/utils/input_handler_utils2.c \
	$(SRC_DIR)/error/error.c \
	$(SRC_DIR)/error/handler_error.c

OBJS        = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Linking Minishell..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -o $(NAME) $(LDFLAGS)
	@echo "Minishell compilation completed!"

$(LIBFT):
	@echo "Compiling Libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "Libft compilation completed!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

test:
	@$(RM) test
	@$(MAKE) -s -C $(LIBFT_DIR)
	@mkdir -p test
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) src/builtin/echo.c src/builtin/echo_test.c $(LIBFT_FLAGS) $(LDFLAGS) \
	-o test/echo
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) src/builtin/pwd.c src/builtin/pwd_test.c $(LIBFT_FLAGS) $(LDFLAGS) \
	-o test/pwd
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) src/builtin/env.c src/builtin/env2.c src/builtin/env3.c \
	src/builtin/env_test.c $(LIBFT_FLAGS) $(LDFLAGS) \
	-o test/env
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) src/builtin/exit.c src/builtin/exit_test.c $(LIBFT_FLAGS) $(LDFLAGS) \
	-o test/exit
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) src/builtin/export.c src/builtin/export_test.c src/builtin/env.c \
	src/builtin/env2.c src/builtin/env3.c $(LIBFT_FLAGS) $(LDFLAGS) \
	-o test/export
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) src/builtin/unset.c src/builtin/unset_test.c src/builtin/env.c \
	src/builtin/env2.c src/builtin/env3.c $(LIBFT_FLAGS) $(LDFLAGS) \
	-o test/unset
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) src/signals/signals_test.c src/signals/signals_interactive.c \
	src/signals/signals_execution.c src/signals/signals_heredoc.c src/signals/signals_reset.c \
	src/signals/signals_setup.c src/signals/signals_state.c $(LIBFT_FLAGS) $(LDFLAGS) \
	-o test/signals
# echo
	@(./test/echo hola que tal > test/my_echo.txt; \
	echo hola que tal > test/bash_echo.txt; \
	diff test/my_echo.txt test/bash_echo.txt && echo "OK: echo hola que tal" || echo "FAIL: echo hola que tal")
# echo -n
	@(./test/echo -n hola que tal > test/my_echo.txt; \
	echo -n hola que tal > test/bash_echo.txt; \
	diff test/my_echo.txt test/bash_echo.txt && echo "OK: echo -n hola que tal" || echo "FAIL: echo -n hola que tal")
# echo -n -nn
	@(./test/echo -n -nn hola que tal > test/my_echo.txt; \
	echo -n -nn hola que tal > test/bash_echo.txt; \
	diff test/my_echo.txt test/bash_echo.txt && echo "OK: echo -n -nn hola que tal" || echo "FAIL: echo -n -nn hola que tal")
# echo -n -n -n
	@(./test/echo -n -n -n hola que tal > test/my_echo.txt; \
	echo -n -n -n hola que tal > test/bash_echo.txt; \
	diff test/my_echo.txt test/bash_echo.txt && echo "OK: echo -n -n -n hola que tal" || echo "FAIL: echo -n -n -n hola que tal")
# pwd
	@(./test/pwd > test/my_pwd.txt; \
	pwd > test/bash_pwd.txt; \
	diff test/my_pwd.txt test/bash_pwd.txt && echo "OK: pwd" || echo "FAIL: pwd")
# unset pwd before
	@(unset PWD; \
	./test/pwd > test/my_pwd.txt; \
	pwd > test/bash_pwd.txt; \
	diff test/my_pwd.txt test/bash_pwd.txt && echo "OK: pwd (unset env PWD)" || echo "FAIL: pwd (unset env PWD)")
# env
	@(./test/env > test/my_env.txt; \
	env > test/bash_env.txt; \
	diff <(grep -v '^_=' test/my_env.txt) <(grep -v '^_=' test/bash_env.txt) && echo "OK: env (print env)" || echo "FAIL: env (print env)")
# export
#	@(./test/export > test/my_export.txt; \
	export > test/bash_export.txt; \
	diff test/my_export.txt test/bash_export.txt && echo "OK: export" || echo "FAIL: export")
# unset
#	@(./test/unset > test/my_unset.txt; \
	unset > test/bash_unset.txt; \
	diff test/my_unset.txt test/bash_unset.txt && echo "OK: unset" || echo "FAIL: unset")
	@echo "Test manually \`unset\` and \`export\`"

.PHONY: all clean fclean re test