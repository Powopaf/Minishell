/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:23:05 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/26 23:48:31 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../../error/err.h"
#include "../../func/func.h"
#include "parser_cmd.h"

char	*get_env(t_shell *sh, char *var_name)
{
	char	*var;
	size_t	i;

	i = 0;
	while (sh->envp && sh->envp[i])
	{
		if (!ft_strncmp(var_name, sh->envp[i], ft_strlen(var_name))
			&& sh->envp[i][ft_strlen(var_name)] == '=')
		{
			var = ft_substr(sh->envp[i], ft_strlen(var_name) + 1,
					ft_strlen(sh->envp[i]) - (ft_strlen(var_name) + 1));
			if (!var)
				error(sh, "malloc", strerror(errno), -FAIL);
			return (var);
		}
		i++;
	}
	var = ft_strdup("");
	if (!var)
		error(sh, "malloc", strerror(errno), -FAIL);
	return (var);
}

static int	is_builtin_p2(char *cmd, t_shell *sh, char **args)
{
	if (!ft_strncmp(cmd, "pwd", 4))
	{
		sh->status = pwd(args, sh);
		return (1);
	}
	if (!ft_strncmp(cmd, "export", 7))
	{
		sh->status = export(args, sh);
		return (1);
	}
	if (!ft_strncmp(cmd, "env", 4))
	{
		sh->status = env(args, sh);
		return (1);
	}
	if (!ft_strncmp(cmd, "unset", 6))
	{
		sh->status = unset(args, sh);
		return (1);
	}
	return (0);
}

int	is_builtin(char *cmd, t_shell *sh, char **args)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "exit", 5))
	{
		ft_exit(args, sh);
	}
	if (!ft_strncmp(cmd, "echo", 5))
	{
		sh->status = echo(args, sh);
		return (1);
	}
	if (!ft_strncmp(cmd, "cd", 3))
	{
		sh->status = cd(sh, args);
		return (1);
	}
	return (is_builtin_p2(cmd, sh, args));
}

int	is_builtin_main(t_shell *sh, t_ast *node, char *cmd, char **args)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "exit", 5))
	{
		ft_exit(args, sh);
	}
	if (!ft_strncmp(cmd, "cd", 3))
	{
		node->status = cd(sh, args);
		return (1);
	}
	if (!ft_strncmp(cmd, "export", 7) && args[1])
	{
		node->status = export(args, sh);
		return (1);
	}
	if (!ft_strncmp(cmd, "unset", 6))
	{
		node->status = unset(args, sh);
		return (1);
	}
	return (0);
}
