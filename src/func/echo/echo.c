/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:25:35 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/11 11:40:22 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../func.h"
#include <stdio.h>
#include <stdlib.h>

static int trim(char *str)
{
	size_t i;

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

void echo(char **args, t_shell *sh)
{
	size_t i;
	int n_flag;

	i = 1;
	n_flag = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		n_flag = 0;
		i++;
	}
	while (args[i])
	{
		if (trim(args[i]) == -1)
		{
			sh->status = EXIT_FAILURE;
			exit(EXIT_FAILURE);
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag)
		printf("\n");
	sh->status = EXIT_SUCCESS;
	exit(EXIT_SUCCESS);
}
