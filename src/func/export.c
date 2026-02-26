/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 09:26:12 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/26 09:25:43 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"
#include "../../libft/libft.h"
#include "../error/err.h"
#include <stdlib.h>
#include <stdio.h>

static int	exist(char *var, char ***env)
{
	int		key_len;
	char	*dup;
	int		i;

	key_len = 0;
	while (var[key_len] && var[key_len] != '=')
		key_len++;
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], var, key_len)
			&& (*env)[i][key_len] == '=')
		{
			dup = ft_strdup(var);
			if (!dup)
				return (EXIT_FAILURE);
			free((*env)[i]);
			(*env)[i] = dup;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

static int	join(char ***env, char *var)
{
	char	**new_env;
	char	*dup;
	int		i;

	if (exist(var, env) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	new_env = malloc(sizeof(char *) * (ft_strlendouble(*env) + 2));
	if (!new_env)
		return (EXIT_FAILURE);
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	dup = ft_strdup(var);
	if (!dup)
		return (free(new_env), EXIT_FAILURE);
	new_env[i] = dup;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (EXIT_SUCCESS);
}

static int	set_var(char **args, int i, int j, t_shell *sh)
{
	char	*tmp;

	if (args[i][j] == '=')
	{
		if (join(&sh->envp, args[i]) == EXIT_FAILURE)
			return (error(sh, "malloc", strerror(errno), EXIT_FAILURE),
				EXIT_FAILURE);
	}
	else
	{
		tmp = ft_strjoin_char(args[i], '=', 1, 0);
		if (!tmp)
			return (error(sh, "malloc", strerror(errno), EXIT_FAILURE),
				EXIT_FAILURE);
		if (join(&sh->envp, tmp) == EXIT_FAILURE)
			return (free(tmp), error(sh, "malloc",
					strerror(errno), EXIT_FAILURE),
				EXIT_FAILURE);
		free(tmp);
	}
	return (EXIT_SUCCESS);
}

static int	add_var(char **args, t_shell *sh)
{
	int		i;
	int		j;

	i = 0;
	while (args[++i])
	{
		j = -1;
		if (!args[i][++j] || ((ft_isalnum(args[i][j]) && ft_isdigit(args[i][j]))
				|| (!ft_isalnum(args[i][j]) && args[i][j] != '_')))
		{
			export_msg(sh, args[i]);
			continue ;
		}
		while (args[i][++j] && args[i][j] != '=')
		{
			if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
			{
				export_msg(sh, args[i]);
				continue ;
			}
		}
		if (set_var(args, i, j, sh) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export(char **args, t_shell *sh)
{
	int		i;

	i = 0;
	if (!args[1])
	{
		while (sh->envp && sh->envp[++i])
			printf("export %s\n", sh->envp[i]);
		return (SUCCESS);
	}
	if (add_var(args, sh) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
