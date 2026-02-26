/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:25:35 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/26 09:58:36 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../error/err.h"
#include "func.h"
#include <stdlib.h>
#include <unistd.h>

static void	printout(char **args, size_t i)
{
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
}

int	echo(char **args, t_shell *sh)
{
	size_t	i;
	size_t	j;
	int		n_flag;

	i = 0;
	n_flag = 1;
	while (args[++i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (!args[i][j])
			n_flag = 0;
		if (args[i][j] && args[i][j] != 'n')
			break ;
	}
	printout(args, i);
	if (n_flag)
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			error(sh, "write", strerror(errno), -FAIL);
	return (SUCCESS);
}
