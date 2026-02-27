/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:59:55 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/27 11:46:17 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../error/err.h"
#include "../exec/exec_utils.h"
#include "../exec/parser_cmd/parser_cmd.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	complete_path(t_shell *sh, char *path, char **new_wd)
{
	char	*home;

	if (!path || path[0] == '\0' || (path[0] == '~' && !path[1])
		|| (path[0] == '~' && path[1] == '/'))
	{
		home = get_env(sh, "HOME");
		if (!home)
			return (error(sh, "cd", "HOME not set", -FAIL), 0);
		if (!path || path[0] == '\0')
			*new_wd = ft_strdup(home);
		if (path && ((path[0] == '~' && !path[1]) || (path[0] == '~'
					&& path[1] == '/')))
			*new_wd = ft_strjoin(home, path + 1);
		free(home);
		if (!*new_wd)
			return (error(sh, "cd", strerror(errno), -FAIL), 0);
		return (1);
	}
	*new_wd = ft_strdup(path);
	if (!*new_wd)
		return (error(sh, "cd", strerror(errno), -FAIL), 0);
	return (1);
}

static int	update_envp(t_shell *sh, char *new_wd)
{
	char	*entry;
	size_t	i;

	entry = ft_strjoin("PWD=", new_wd);
	free(new_wd);
	if (!entry)
		return (error(sh, "cd", strerror(errno), -FAIL), 0);
	i = 0;
	while (sh->envp && sh->envp[i])
	{
		if (!ft_strncmp("PWD", sh->envp[i], 3) && sh->envp[i][3] == '=')
		{
			free(sh->envp[i]);
			sh->envp[i] = entry;
			return (1);
		}
		i++;
	}
	if (!ft_addstr_arr(&sh->envp, entry))
		return (free(entry), 0);
	free(entry);
	return (1);
}
static int	replace_oldpwd(t_shell *sh, char *wd)
{
	char	*entry;
	size_t	i;

	entry = ft_strjoin("OLDPWD=", wd);
	free(wd);
	if (!entry)
		return (error(sh, "malloc", strerror(errno), -FAIL), 0);
	i = 0;
	while (sh->envp && sh->envp[i])
	{
		if (!ft_strncmp("OLDPWD", sh->envp[i], 6) && sh->envp[i][6] == '=')
		{
			free(sh->envp[i]);
			sh->envp[i] = entry;
			return (1);
		}
		i++;
	}
	if (!ft_addstr_arr(&sh->envp, entry))
		return (free(entry), 0);
	free(entry);
	return (1);
}

int	cd(t_shell *sh, char **args)
{
	char	*wd;
	char	*new_wd;
	char	*err;

	if (args[1] && args[2])
		return (error(sh, "cd", "too many arguments", -FAIL), FAIL);
	wd = get_cwd(sh);
	if (wd == NULL)
		return (error(sh, "cd", strerror(errno), -FAIL), FAIL);
	new_wd = NULL;
	if (!complete_path(sh, args[1], &new_wd))
		return (free(wd), FAIL);
	if (chdir(new_wd) == -1)
	{
		err = error_mess("cd", new_wd);
		error(sh, err, strerror(errno), -FAIL);
		return (free(wd), free(new_wd), free(err), FAIL);
	}
	free(new_wd);
	new_wd = get_cwd(sh);
	replace_oldpwd(sh, wd);
	update_envp(sh, new_wd);
	sh->status = 0;
	return (SUCCESS);
}
