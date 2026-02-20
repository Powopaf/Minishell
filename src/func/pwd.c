/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:18:42 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/20 11:03:13 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../error/err.h"
#include "../exec/parser_cmd/parser_cmd.h"
#include "../../libft/libft.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>

static void	error_msg(char *arg, t_shell *sh)
{
	char	*msg;

	msg = ft_strjoin("pwd: ", arg);
	if (!msg)
	{
		error(sh, "pwd", "memory allocation error", 1);
		return ;
	}
	error(sh, "pwd", msg, 1);
}

void	pwd(char **args, t_shell *sh)
{
	char	*pwd;

	if (args[1] && args[1][0] != '-')
	{
		error_msg(args[1], sh);
		return ;
	}
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
