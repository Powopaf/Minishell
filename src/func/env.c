/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:44:02 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/16 18:43:36 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"
#include "../error/err.h"
#include <stdio.h>

void	env(char **args, t_shell *sh)
{
	size_t	i;

	if (args[1])
	{
		error(sh, "env", "too many arguments", 1);
		return ;
	}
	i = 0;
	while (sh->envp && sh->envp[i])
	{
		if (printf("%s\n", sh->envp[i]) == -1)
		{
			error(sh, "env", "printf error", 1);
			return ;
		}
		i++;
	}
	sh->status = 0;
}
