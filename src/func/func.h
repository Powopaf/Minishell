#ifndef FUNC_H
#define FUNC_H

#include "../../struct.h"

int		ft_exit(char **args, t_shell *sh);
void	echo(char **args, t_shell *sh);
void	pwd(char **args, t_shell *sh);
void	cd(t_shell *sh, char **args);

#endif
