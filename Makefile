.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address
LIB = -fsanitize=address
SRC = ./minishell.c \
	  ./src/error/err.c \
	  ./src/init/init_shell.c \
	  ./src/token/tokens.c \
	  ./src/token/tokens_add.c \
	  ./src/token/tokens_lst_utils.c \
	  ./src/token/tokens_utils.c \


OBJ_DIR = .obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.d))

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $+ $(LIB)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all
