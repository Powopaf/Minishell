/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:23:56 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 01:03:22 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/4_builtin_functions/func.h"
#include "./src/6_cleaning/clean_shell.h"
#include "./src/7_error_handling/err.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_isnumber(char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

void	ft_exit(char **args, t_shell *sh)
{
	unsigned int	exitno;

	if (args && args[1] && !ft_isnumber(args[1]))
	{
		error(sh, error_mess("exit", args[1]), "numeric argument required",
			MISUSE);
	}
	else if (args && args[1] && args[2])
		error(sh, "exit", "too many arguments", FAIL);
	else if (args && args[1])
	{
		exitno = ft_atoi(args[1]) % 256;
	}
	else
		exitno = sh->status;
	if (sh->tty)
		write(STDOUT_FILENO, "exit\n", 5);
	clean_shell(sh);
	close_std_fds();
	exit(exitno);
}
