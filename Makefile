.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address -I. -Iincludes
LIB = -fsanitize=address
SRC = 
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
