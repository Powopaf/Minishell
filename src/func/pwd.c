/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:18:42 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/25 12:14:58 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../error/err.h"
#include "../exec/parser_cmd/parser_cmd.h"
#include "func.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

// void	pwd(char **args, t_shell *sh)
// {
// 	char	*pwd;

// 	(void)args;
// 	pwd = get_env(sh, "PWD");
// 	if (!pwd || pwd[0] == '\0')
// 	{
// 		free(pwd);
// 		pwd = get_env(sh, "OLDPWD");
// 		if (!pwd || pwd[0] == '\0')
// 		{
// 			free(pwd);
// 			sh->status = EXIT_FAILURE;
// 			return ;
// 		}
// 	}
// 	if (printf("%s\n", pwd) < 0)
// 	{
// 		error(sh, "pwd", "write error", 1);
// 		free(pwd);
// 		return ;
// 	}
// 	free(pwd);
// 	sh->status = EXIT_SUCCESS;
// 	return ;
// }

void	pwd(char **args, t_shell *sh)
{
	char *cwd;

	(void)args;
	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		cwd = ft_strjoin_char_p(&cwd, '\n', 1, 1);
		write(1, cwd, ft_strlen(cwd));
		if (cwd)
			free(cwd);
		sh->status = 0;
		return ;
	}
	error(sh, "pwd", strerror(errno), -FAIL);
	return ;
}
