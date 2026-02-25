/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:23:05 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/25 19:36:03 by flomulle         ###   ########.fr       */
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

int	is_builtin(char *cmd, t_shell *sh, char **args)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "exit", 5))
		return (ft_exit(args, sh), 1);
	if (!ft_strncmp(cmd, "echo", 5))
		return (echo(args, sh), 1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (cd(sh, args), 1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (pwd(args, sh), 1);
	if (!ft_strncmp(cmd, "export", 7))
		return (export(args, sh), 1);
	if (!ft_strncmp(cmd, "env", 4))
		return (env(args, sh), 1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (unset(args, sh), 1);
	return (0);
}

int	is_builtin_main(char *cmd, t_shell *sh, char **args)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "exit", 5))
		return (ft_exit(args, sh), 1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (cd(sh, args), 1);
	if (!ft_strncmp(cmd, "export", 7))
		return (export(args, sh), 1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (unset(args, sh), 1);
	return (0);
}
