/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:18:42 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/12 12:27:01 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../error/err.h"
#include "../../exec/parser_cmd/parser_cmd.h"
#include "../func.h"
#include <stdio.h>
#include <stdlib.h>

void pwd(char **args, t_shell *sh)
{
	char *pwd;

	if (args[1])
	{
		error(sh, "pwd", "too many arguments", 1);
		sh->status = EXIT_FAILURE;
		return;
	}
	pwd = get_env(sh, "PWD");
	if (!pwd)
	{
		error(sh, "pwd", "PWD not set", 1);
		sh->status = EXIT_FAILURE;
		return;
	}
	if (printf("%s\n", pwd) < 0)
	{
		error(sh, "pwd", "write error", 1);
		sh->status = EXIT_FAILURE;
		free(pwd);
		return;
	}
	free(pwd);
	sh->status = EXIT_SUCCESS;
	return;
}
