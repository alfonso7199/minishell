# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 22:37:10 by rzt               #+#    #+#              #
#    Updated: 2025/07/04 17:30:55 by rzt              ###   ########.fr        #
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

.PHONY: all clean fclean re