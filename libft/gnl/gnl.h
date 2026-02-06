#ifndef GNL_H
# define GNL_H

# define BUFFER_SIZE 4096
# define FD_MAX 16

#include "stdlib.h"

size_t	strlen_gnl(const char *s);
char	*strchr_gnl(const char *s, int c);
char	*strjoin_gnl(char *s1, char *s2);
void	cpy_gnl(char *res, char *s1, char *s2);

#endif
