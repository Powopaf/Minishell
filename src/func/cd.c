/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:59:55 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/25 10:39:25 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../error/err.h"
#include "../exec/parser_cmd/parser_cmd.h"
#include "func.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	verif(char *new_pwd, t_shell *sh)
{
	if (!new_pwd)
		return (error(sh, "cd", strerror(errno), 1), 1);
	return (0);
}

static int	is_full_path(t_shell *sh, char *path, char **new_pwd)
{
	char	*home;

	if (!path || path[0] == '\0')
	{
		home = get_env(sh, "HOME");
		if (!home)
			return (error(sh, "cd", "HOME not set", 1), 1);
		*new_pwd = ft_strdup(home);
		return (free(home), verif(*new_pwd, sh));
	}
	if (path[0] == '~')
	{
		home = get_env(sh, "HOME");
		if (!home)
			return (error(sh, "cd", "HOME not set", 1), 1);
		*new_pwd = ft_strjoin(home, path + 1);
		return (free(home), verif(*new_pwd, sh));
	}
	*new_pwd = ft_strdup(path);
	return (verif(*new_pwd, sh));
}

static int	replace_envp(t_shell *sh)
{
	char	*new_pwd;
	char	*entry;
	size_t	i;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (error(sh, "malloc", strerror(errno), 1), 1);
	entry = ft_strjoin("PWD=", new_pwd);
	free(new_pwd);
	if (!entry)
		return (error(sh, "malloc", strerror(errno), 1), 1);
	i = -1;
	while (sh->envp && sh->envp[++i])
	{
		if (!ft_strncmp("PWD", sh->envp[i], 3) && sh->envp[i][3] == '=')
		{
			free(sh->envp[i]);
			sh->envp[i] = entry;
			return (0);
		}
	}
	return (free(entry), 0);
}
static int	replace_oldpwd(t_shell *sh, char *w_dir)
{
	char	*entry;
	size_t	i;

	entry = ft_strjoin("OLDPWD=", w_dir);
	if (!entry)
		return (error(sh, "malloc", strerror(errno), 1), 1);
	i = -1;
	while (sh->envp && sh->envp[++i])
	{
		if (!ft_strncmp("OLDPWD", sh->envp[i], 6) && sh->envp[i][6] == '=')
		{
			free(sh->envp[i]);
			sh->envp[i] = entry;
			return (0);
		}
	}
	return (free(entry), 0);
}

void	cd(t_shell *sh, char **args)
{
	char	*w_dir;
	char	*new_pwd;
	char	*err_msg;

	if (args[1] && args[2])
		return (error(sh, "cd", "too many arguments", 1));
	w_dir = getcwd(NULL, 0);
	if (w_dir == NULL)
		return (error(sh, "malloc", strerror(errno), 1));
	new_pwd = NULL;
	if (is_full_path(sh, args[1], &new_pwd))
		return (free(w_dir));
	if (chdir(new_pwd) == -1)
	{
		err_msg = ft_strjoin(new_pwd, ": No such file or directory");
		return (error(sh, "cd", err_msg, 1), free(err_msg), free(w_dir),
			free(new_pwd));
	}
	if (replace_oldpwd(sh, w_dir) || replace_envp(sh))
		error(sh, "cd", "can not update PWD", 1);
	else
	{
		sh->status = 0;
	}
	return (free(w_dir), free(new_pwd));
}
