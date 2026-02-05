#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

#include "../../struct.h"

typedef struct s_redir
{
	t_token_kw		kw;
	char			*file;
	char			*eofkw;
	int				fd_in;
	int				fd_out;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

int	parse_redir(t_shell *sh, t_ast *ast_node, t_token **token);
int	parse_command_args(t_shell *sh, t_ast *node, t_token **tokens);

#endif
