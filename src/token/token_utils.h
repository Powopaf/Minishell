#ifndef TOKENS_UTILS_H
# define TOKENS_UTILS_H

# include "../../struct.h"

#define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

int	isshspace(char c);
int	isshbreak(char c);
int	isshellkw(char c);
ssize_t	add_key_token(t_shell *sh, ssize_t i);
int	add_token(t_shell *sh, char *token, t_token_kw kw);

#endif
