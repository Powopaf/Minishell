/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:18:42 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/23 13:00:59 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../error/err.h"
#include "../exec/parser_cmd/parser_cmd.h"
#include "func.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	pwd(char **args, t_shell *sh)
{
	char	*pwd;
	
	(void)args;
	pwd = get_env(sh, "PWD");
	if (!pwd || pwd[0] == '\0')
	{
		free(pwd);
		pwd = get_env(sh, "OLDPWD");
		if (!pwd || pwd[0] == '\0')
		{
			free(pwd);
			sh->status = EXIT_FAILURE;
			return ;
		}
	}
	if (printf("%s\n", pwd) < 0)
	{
		error(sh, "pwd", "write error", 1);
		free(pwd);
		return ;
	}
	free(pwd);
	sh->status = EXIT_SUCCESS;
	return ;
}
