/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:23:56 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/09 13:32:10 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../func.h"
#include "../../../libft/libft.h"
#include "../../error/err.h"

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
	int	exit_code;

	if (nb_args(args) > 2)
	{
		error(sh, "exit", "too many arguments", 1);
		return (-1);
	}
	exit_code = sh->status;
	if (args && args[1])
	{
		exit_code = ft_atoi(args[1]);
	}
	sh->exit = exit_code;
	return (exit_code);
}
