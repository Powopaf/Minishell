.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address
LIB = libft/libft.a -lreadline -fsanitize=address
SRC = ./minishell.c \
	  ./src/error/err.c \
	  ./src/init/init_shell.c \
	  ./src/clean/clean_utils.c \
	  ./src/clean/clean_shell.c \
	  ./src/exec/exec.c \
	  ./src/exec/exec_cmd.c \
	  ./src/exec/exec_redir.c \
	  ./src/exec/exec_utils.c \
	  ./src/exec/parser_cmd/utils_parse_cmd.c \
	  ./src/exec/parser_cmd/parser_cmd.c \
	  ./src/parsing/parsing.c \
	  ./src/parsing/parsing_cmd.c \
	  ./src/parsing/parsing_redir.c \
	  ./src/parsing/ast/ast_utils.c \
	  ./src/parsing/expend/expand.c \
	  ./src/parsing/expend/expand_env.c \
	  ./src/parsing/token/syntax/syntax.c \
	  ./src/parsing/token/put_token.c \
	  ./src/parsing/token/tokens.c \
	  ./src/parsing/token/tokens_add.c \
	  ./src/parsing/token/tokens_lst_utils.c \
	  ./src/parsing/token/tokens_utils.c \
	  ./src/signal/signal.c \
	  ./src/signal/signal_fork.c \
	  ./src/signal/signal_utils.c \
	  ./src/exec/pipe.c \
	  ./src/heredocs/heredoc.c \
	  ./src/func/exit/exit.c \
	  ./src/func/echo/echo.c \
	  ./src/func/pwd/pwd.c \
	  ./src/func/cd/cd.c

OBJ_DIR = .obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.d))

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) -o $(NAME) $(OBJ) $(LIB)

libft/libft.a:
	$(MAKE) -C libft

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
