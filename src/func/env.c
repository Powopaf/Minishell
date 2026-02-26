/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:44:02 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/26 09:58:58 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"
#include "../error/err.h"
#include <stdio.h>

int	env(char **args, t_shell *sh)
{
	size_t	i;

	if (args[1])
	{
		error(sh, "env", "too many arguments", FAIL);
		return (FAIL);
	}
	i = 0;
	while (sh->envp && sh->envp[i])
	{
		if (printf("%s\n", sh->envp[i]) == -1)
		{
			error(sh, "env", "printf error", FAIL);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}
