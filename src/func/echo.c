/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:25:35 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/20 10:52:36 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../error/err.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>

static int	trim(char *str)
{
	size_t	i;

	if (str[0] != '"')
		return (printf("%s", str));
	i = 1;
	while (str[i] != '"')
	{
		if (printf("%c", str[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	echo(char **args, t_shell *sh)
{
	size_t	i;
	int		n_flag;

	i = 0;
	n_flag = 1;
	while (args[++i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		n_flag = 0;
		continue ;
	}
	while (args[i])
	{
		if (trim(args[i]) == -1)
		{
			error(sh, "echo", "printf error", 1);
			return ;
		}
		if (args[i + 1] && printf(" ") == -1)
			error(sh, "echo", "printf error", 1);
		i++;
	}
	if (n_flag && printf("\n") == -1)
		error(sh, "echo", "printf error", 1);
	sh->status = EXIT_SUCCESS;
	return ;
}
