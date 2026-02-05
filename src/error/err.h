#ifndef ERR_H
# define ERR_H

#include "../../struct.h"

# define SUCCESS 0
# define FAIL 1
# define MALLOC_ERR "Memory allocation failed"
# define MALLOC_FULL_ERR "minishell: malloc: Memory allocation failed"
# define QUOTE_ERR "expected end-quote"
# define PARENTH_ERR "missing a parenthesis"
# define PIPE_ERR "piping wrong"
# define PROMPT_MES "minishell: "
# define CMD_NOT_FND 127
# define CMD_PERM_DND 126
# define MISUSE 2
# define PRG_ERR 666
//# define SIG_BASE 128

//# define ISDIR "Is a directory"
# define DEBUG "PROGRAM ERROR"



void	syntax_error(t_shell *sh, t_token_kw kw, int exitno);
void	error(t_shell *shell, char *context, char *why, int exitno);

#endif
