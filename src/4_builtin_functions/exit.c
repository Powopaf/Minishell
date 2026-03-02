/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:23:56 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 16:02:14 by flomulle         ###   ########.fr       */
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

void	ft_exit(t_shell *sh, char **args)
{
	unsigned int	exitno;

	exitno = SUCCESS;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		write(STDERR_FILENO, "exit\n", 5);
	if (args && args[1] && !ft_isnumber(args[1]))
	{
		error(sh, error_mess("exit", args[1]), "numeric argument required",
			MISUSE);
	}
	else if (args && args[1] && args[2])
	{
		error(sh, "exit", "too many arguments", -FAIL);
		return ;
	}
	else if (args && args[1])
	{
		exitno = ft_atoi(args[1]) % 256;
	}
	else
		exitno = sh->status;
	clean_shell(sh);
	close_std_fds();
	exit(exitno);
}
