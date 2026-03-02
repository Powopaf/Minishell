/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:44:02 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 01:03:19 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/4_builtin_functions/func.h"
#include "./src/7_error_handling/err.h"
#include <stdlib.h>
#include <unistd.h>

int	env(char **args, t_shell *sh)
{
	size_t	i;
	char	*tmp;

	if (args[1])
	{
		error(sh, "env", "too many arguments", -FAIL);
		return (FAIL);
	}
	i = 0;
	while (sh->envp && sh->envp[i])
	{
		if (ft_strchr(sh->envp[i], '='))
		{
			tmp = ft_strjoin_char(sh->envp[i], '\n', 1, 0);
			if (!tmp)
			{
				error(sh, "env", strerror(errno), -FAIL);
				return (FAIL);
			}
			write(STDOUT_FILENO, tmp, ft_strlen(tmp));
			free(tmp);
		}
		i++;
	}
	return (SUCCESS);
}
