.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
LIB =
SRC = ./ft_add_str_array.c \
	  ./ft_empty_array_strs.c \
	  ./ft_free_array_strs.c \
	  ./ft_add_arr_arr.c \
	  ./ft_addstr_arr.c \
	  ./ft_isalnum.c \
	  ./ft_itoa.c \
	  ./ft_ptoa.c \
	  ./ft_putendl_fd.c \
	  ./ft_putstr_fd.c \
	  ./ft_split.c \
	  ./ft_strchr.c \
	  ./ft_strcmp.c \
	  ./ft_strdup.c \
	  ./ft_strdup.c \
	  ./ft_strjoin.c \
	  ./ft_strjoin_char.c \
	  ./ft_strjoin_char_p.c \
	  ./ft_strjoin_free.c \
	  ./ft_strlen.c \
	  ./ft_strlen.c \
	  ./ft_strncmp.c \
	  ./ft_strncmp.c \
	  ./ft_strrchr.c \
	  ./ft_strsdup.c \
	  ./ft_substr.c \
	  ./gnl/ft_get_next_line.c \
	  ./gnl/ft_get_next_line_utils.c \
	  ./ft_memcpy.c \
	  ./ft_atoi.c \
	  ./ft_isdigit.c \
	  ./ft_close_fd.c

OBJ_DIR = .obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.d))

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
		ar -rsc $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
