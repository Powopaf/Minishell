/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:23:05 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/04 16:35:35 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../../error/err.h"
#include "../../func/func.h"
#include "parser_cmd.h"

char *get_env(t_shell *sh, char *var_name)
{
	char *var;
	size_t i;

	i = 0;
	while (sh->envp && sh->envp[i])
	{
		if (!ft_strncmp(var_name, sh->envp[i], ft_strlen(var_name)) &&
			sh->envp[i][ft_strlen(var_name)] == '=')
		{
			var = ft_substr(sh->envp[i], ft_strlen(var_name) + 1,
							ft_strlen(sh->envp[i]) - (ft_strlen(var_name) + 1));
			if (!var)
				error(sh, "malloc", MALLOC_ERR, -FAIL);
			return (var);
		}
		i++;
	}
	var = ft_strdup("");
	if (!var)
		error(sh, "malloc", MALLOC_ERR, -FAIL);
	return (var);
}

int is_builtin(char *cmd, t_shell *sh, char **args)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
	{
		ft_exit(args, sh);
		return (1);
	}
	if (ft_strncmp(cmd, "echo", 5) == 0)
	{
		echo(args, sh);
		return (2);
	}
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (3);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
	{
		pwd(args, sh);
		return (4);
	}
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (5);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (6);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (7);
	return (0);
}
