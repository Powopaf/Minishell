/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:18:42 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/25 12:17:40 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../error/err.h"
#include "../exec/parser_cmd/parser_cmd.h"
#include "func.h"
#include <stdlib.h>
#include <unistd.h>

void	pwd(char **args, t_shell *sh)
{
	char	*cwd;

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
