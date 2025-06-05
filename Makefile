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
	# $(SRC_DIR)/error/error.c \
	$(SRC_DIR)/execution/executor.c \
	$(SRC_DIR)/parsing/parser.c \
	$(SRC_DIR)/tokenizing/tokenizer.c \
	$(SRC_DIR)/utils/signals.c \

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
	@mkdir -p test
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) src/builtin/echo.c src/builtin/echo_test.c $(LIBFT_FLAGS) -o test/echo
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) src/builtin/pwd.c src/builtin/pwd_test.c $(LIBFT_FLAGS) -o test/pwd
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

.PHONY: all clean fclean re test