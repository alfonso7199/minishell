NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
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
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

test:
	@$(RM) -rf test
	@mkdir -p test
	@$(CC) $(CFLAGS) src/builtin/echo.c src/builtin/echo_test.c $(LIBFT_FLAGS) -o test/echo
	@$(CC) $(CFLAGS) src/builtin/pwd.c src/builtin/pwd_test.c $(LIBFT_FLAGS) -o test/pwd

	@./test/echo hola que tal > test/my_echo.txt
	@echo hola que tal > test/bash_echo.txt
	@diff test/my_echo.txt test/bash_echo.txt && echo "OK: echo hola que tal" || echo "FAIL: echo hola que tal"
	
	@./test/echo -n hola que tal > test/my_echo.txt
	@echo -n hola que tal > test/bash_echo.txt
	@diff test/my_echo.txt test/bash_echo.txt && echo "OK: echo -n hola que tal" || echo "FAIL: echo -n hola que tal"

	@./test/pwd > test/my_pwd.txt
	@pwd > test/bash_pwd.txt
	@diff test/my_pwd.txt test/bash_pwd.txt && echo "OK: pwd" || echo "FAIL: pwd"

.PHONY: all clean fclean re test