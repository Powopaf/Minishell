#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>

typedef enum e_token_kw
{
	EOFKW,
	REDIR_IN,
	REDIR_HD,
	REDIR_OUT,
	REDIR_APP,
	PIPE,
	L_PARENTH,
	R_PARENTH,
	SEMICOLON,
	AMPERSAND,
	AND,
	OR,
	WORD,
	FLAG,
	VAR,
}	t_token_kw;

typedef enum e_ast_node
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL
}	t_ast_node_type;

typedef struct s_ast
{
	t_ast_node_type	astkw;
	char			**args;
	struct s_redir	*redir;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	int				status;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_token
{
	t_token_kw		kw;
	char	*token;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	char	**envp;
	char	*name;
	int		status;
	int		stdin_fd;
	int		stdout_fd;
	int		hd_fd;
	char	*file;
	int		cmd_cnt;
	char	*line;
	t_token	*tokens;
	t_ast	*ast;
}	t_shell;

#endif
