/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:23:56 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/16 18:51:57 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"
#include "../../libft/libft.h"
#include "../error/err.h"
#include <stdlib.h>

static int	nb_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_exit(char **args, t_shell *sh)
{
	char	*msg;

	if (args && args[1] && !ft_isdigit(args[1][0]) &&
		args[1][0] != '-' && args[1][0] != '+')
	{
		msg = ft_strjoin("exit: ", args[1]);
		if (!msg)
			error(sh, "malloc", MALLOC_ERR, 1);
		else
		{
			error(sh, msg, "numeric argument required", 1);
			free(msg);
			sh->exit = 2;
		}
	}
	else if (nb_args(args) > 2)
	{
		error(sh, "exit", "too many arguments", 1);
		return (1);
	}
	else if (args && args[1])
		sh->exit = (unsigned char)ft_atoi(args[1]);
	else
		sh->exit = sh->status;
	return (sh->exit);
}
