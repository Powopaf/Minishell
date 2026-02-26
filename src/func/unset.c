/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 10:34:35 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/26 22:54:39 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../error/err.h"
#include "../exec/parser_cmd/parser_cmd.h"
#include "func.h"
#include <stdlib.h>

static int	is_valid_var_name_unset(t_shell *sh, char *s)
{
	size_t	i;

	(void)sh;
	if (!s || !*s)
		return (1);
	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	env_var_index(t_shell *sh, char *arg)
{
	int	i;

	i = 0;
	while (sh->envp[i])
	{
		if (varcmp(sh->envp[i], arg) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	remove_env_var(t_shell *sh, char *arg)
{
	int		i;
	int		pos;
	char	**new_env;
	size_t	j;

	pos = env_var_index(sh, arg);
	if (pos == -1)
		return (1);
	new_env = malloc((ft_strslen(sh->envp) + 1) * sizeof(char *));
	if (!new_env)
		return (error(sh, "unset", strerror(errno), -FAIL), 0);
	i = 0;
	j = 0;
	while (sh->envp[i])
	{
		if (i != pos)
			new_env[j++] = sh->envp[i];
		else
			free(sh->envp[i]);
		i++;
	}
	new_env[j] = NULL;
	free(sh->envp);
	sh->envp = new_env;
	return (1);
}

static int	unset_var(t_shell *sh, char *arg)
{
	if (!arg[0])
		return (1);
	if (!is_valid_var_name_unset(sh, arg))
		return (1);
	if (!remove_env_var(sh, arg))
		return (0);
	return (1);
}

int	unset(char **args, t_shell *sh)
{
	size_t	i;
	int		status;

	if (!args[1] || !args[1][0])
		return (EXIT_SUCCESS);
	status = SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!unset_var(sh, args[i]))
			status = EXIT_FAILURE;
		i++;
	}
	return (status);
}
