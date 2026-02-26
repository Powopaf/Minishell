/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 09:26:12 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/26 13:44:40 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../error/err.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	new_entry_to_env(t_shell *sh, char *var, char *value)
{
	size_t	i;
	char	**new_env;

	new_env = malloc((ft_strslen(sh->envp) + 2) * sizeof(char *));
	if (!new_env)
		return (error(sh, "export", strerror(errno), -FAIL), 0);
	i = 0;
	while (i < ft_strslen(sh->envp))
	{
		new_env[i] = sh->envp[i];
		i++;
	}
	new_env[i] = create_entry(sh, var, value);
	new_env[i + 1] = NULL;
	free(sh->envp);
	sh->envp = new_env;
	return (1);
}

int	add_to_env(t_shell *sh, char *var, char *value)
{
	size_t	i;

	i = 0;
	while (sh->envp[i])
	{
		if (!varcmp(sh->envp[i], var))
		{
			free(sh->envp[i]);
			sh->envp[i] = create_entry(sh, var, value);
			if (!sh->envp[i])
				return (0);
			return (1);
		}
		i++;
	}
	if (!new_entry_to_env(sh, var, value))
		return (0);
	return (1);
}

int	add_env_var(t_shell *sh, char *arg)
{
	char	*equal;
	char	*var;
	char	*value;
	int		status;

	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		var = ft_strdup(arg);
		value = malloc(1);
	}
	if (equal)
	{
		var = ft_strndup(arg, equal - arg);
		value = ft_strdup(equal + 1);
	}
	if (!is_valid_var_name(sh, arg))
		status = 1;
	else if (equal)
		status = !add_to_env(sh, var, value);
	else
		status = !add_to_env(sh, var, NULL);
	return (free(var), free(value), status);
}

int	printout_env(t_shell *sh)
{
	size_t	len;
	char	**sorted;
	size_t	i;

	len = ft_strslen(sh->envp);
	sorted = malloc((len + 1) * sizeof(char *));
	if (!sorted)
		return (error(sh, "malloc", strerror(errno), -FAIL), 0);
	i = -1;
	while (++i < len)
		sorted[i] = sh->envp[i];
	sorted[i] = NULL;
	sort_ascii(sorted);
	i = 0;
	while (sorted[i])
	{
		if (!printout_env_line(sh, sorted[i]))
		{
			free(sorted);
			return (0);
		}
		i++;
	}
	free(sorted);
	return (1);
}

int	export(char **args, t_shell *sh)
{
	size_t	i;
	int		status;

	if (!args[1])
	{
		if (printout_env(sh))
			return (SUCCESS);
		return (FAIL);
	}
	i = 1;
	status = SUCCESS;
	while (args[i])
	{
		if (add_env_var(sh, args[i]))
			status = FAIL;
		i++;
	}
	return (status);
}
