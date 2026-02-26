.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g #-fsanitize=address
LIB = libft/libft.a -lreadline #-fsanitize=address
SRC = 	./minishell.c \
		./src/0_init/init_shell.c \
		./src/1_tokenization/syntax/syntax_p1.c \
		./src/1_tokenization/syntax/syntax_p2.c \
		./src/1_tokenization/syntax/syntax_quote.c \
		./src/1_tokenization/syntax/syntax_complete.c \
		./src/1_tokenization/syntax/syntax_utils.c \
		./src/1_tokenization/put_token.c \
		./src/1_tokenization/tokens.c \
		./src/1_tokenization/tokens_add.c \
		./src/1_tokenization/tokens_lst_utils.c \
		./src/1_tokenization/tokens_utils.c \
		./src/2_parsing_ast/parsing.c \
		./src/2_parsing_ast/parsing_cmd.c \
		./src/2_parsing_ast/parsing_redir.c \
		./src/2_parsing_ast/parsing_utils.c \
		./src/2_parsing_ast/ast/ast_utils.c \
		./src/exec/expand/expand.c \
		./src/exec/expand/expand_var.c \
		./src/exec/expand/expand_args_split.c \
		./src/exec/expand/expand_custom_split.c \
		./src/exec/expand/expand_wildcards.c \
		./src/exec/expand/expand_wildcards_utils.c \
		./src/exec/expand/expand_env.c \
		./src/exec/expand/expand_rm_quotes.c \
		./src/exec/expand/expand_rm_backslash.c \
		./src/exec/expand/expand_utils.c \
		./src/exec/heredocs/heredoc.c \
		./src/exec/exec.c \
		./src/exec/pipe.c \
		./src/exec/exec_cmd.c \
		./src/exec/exec_cmd_utils.c \
		./src/exec/exec_redir.c \
		./src/exec/exec_utils.c \
		./src/exec/parser_cmd/utils_parse_cmd.c \
		./src/exec/parser_cmd/parser_cmd.c \
		./src/func/cd.c \
		./src/func/echo.c \
		./src/func/env.c \
		./src/func/exit.c \
		./src/func/export.c \
		./src/func/export_utils.c \
		./src/func/pwd.c \
		./src/func/unset.c \
		./src/func/func_utils.c \
		./src/signal/signal.c \
		./src/signal/signal_fork.c \
		./src/signal/signal_utils.c \
		./src/clean/clean_utils.c \
		./src/clean/clean_shell.c \
		./src/error/err.c \
		./src/error/err_syntax.c \
		./src/error/err_utils.c \

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
