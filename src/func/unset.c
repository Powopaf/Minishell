/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 10:34:35 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/25 16:14:56 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"
#include "../error/err.h"
#include "../../libft/libft.h"
#include "../exec/parser_cmd/parser_cmd.h"
#include <stdlib.h>

static void	error_unset(char *arg)
{
	char	*msg;

	msg = ft_strjoin("unset: `", arg);
	if (!msg)
		return (error(NULL, "malloc", strerror(errno), -FAIL));
	error(NULL, "unset", msg, -FAIL);
	free(msg);
}

static int	exist(t_shell *sh, char *var_name)
{
	int		i;
	size_t	len_name;

	if (!sh || !sh->envp || !var_name)
		return (0);
	len_name = ft_strlen(var_name);
	i = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], var_name, len_name) == 0
			&& sh->envp[i][len_name] == '=')
			return (1);
		i++;
	}
	return (0);
}

static int	unset_var(t_shell *sh, char *var_name)
{
	char	**new_envp;
	int		i;
	int		j;
	size_t	len_name;

	if (exist(sh, var_name) == 0)
		return (EXIT_SUCCESS);
	new_envp = malloc(sizeof(char *) * (ft_strlendouble(sh->envp) + 1));
	if (!new_envp)
		return (error(sh, "malloc", strerror(errno), -FAIL), EXIT_FAILURE);
	len_name = ft_strlen(var_name);
	i = 0;
	j = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], var_name, len_name) == 0
			&& sh->envp[i][len_name] == '=')
		{
			free(sh->envp[i++]);
			continue ;
		}
		new_envp[j++] = sh->envp[i++];
	}
	new_envp[j] = NULL;
	return (free(sh->envp), sh->envp = new_envp, EXIT_SUCCESS);
}

void	unset(char **args, t_shell *sh)
{
	int	i;

	if (!args[0] || !args[1])
		return ;
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1])
		{
			error_unset(args[i]);
			return ;
		}
		if (unset_var(sh, args[i]) == EXIT_FAILURE)
			return ;
		i++;
	}
	sh->status = EXIT_SUCCESS;
}
