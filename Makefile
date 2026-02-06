.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address
LIB = -fsanitize=address
SRC = ./minishell.c \
	  ./src/error/err.c \
	  ./src/init/init_shell.c \
	  ./src/clean/clean_redir.c \
	  ./src/clean/clean_shell.c \
	  ./src/exec/exec.c \
	  ./src/exec/exec_cmd.c \
	  ./src/exec/exec_redir.c \
	  ./src/exec/exec_utils.c \
	  ./src/exec/find_cmd.c \
	  ./src/exec/parser_cmd/get_env.c \
	  ./src/exec/parser_cmd/parser_cmd.c \
	  ./src/parsing/parsing.c \
	  ./src/parsing/parsing_cmd.c \
	  ./src/parsing/parsing_redir.c \
	  ./src/parsing/ast/ast_utils.c \
	  ./src/parsing/expend/expand.c \
	  ./src/parsing/expend/expand_env.c \
	  ./src/parsing/token/syntax/syntax.c \
	  ./src/parsing/token/tokens.c \
	  ./src/parsing/token/tokens_add.c \
	  ./src/parsing/token/tokens_lst_utils.c \
	  ./src/parsing/token/tokens_lst_utils.c \
	  ./src/exec/pipe.c \
	  ./src/exec/exec_heredoc.c \

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
