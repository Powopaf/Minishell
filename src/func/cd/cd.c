/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:59:55 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/12 15:14:30 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../error/err.h"
#include "../../exec/parser_cmd/parser_cmd.h"
#include "../func.h"
#include "../../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

static int verif(char *new_pwd, t_shell *sh)
{
	if (!new_pwd)
	{
		error(sh, "cd", MALLOC_ERR, 1);
		return (1);
	}
	return (0);
}

static int	is_full_path(t_shell *sh, char *path, char **new_pwd)
{
	char	*home;

	if (path[0] == '~')
	{
		home = get_env(sh, "HOME");
		*new_pwd = ft_strjoin(home, path + 1);
		free(home);
		return (verif(*new_pwd, sh));
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
		return (error(sh, "malloc", MALLOC_ERR, 1), 1);
	entry = ft_strjoin("PWD=", new_pwd);
	free(new_pwd);
	if (!entry)
		return (error(sh, "malloc", MALLOC_ERR, 1), 1);
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
	free(entry);
	return (0);
}

static void move(char *path, t_shell *sh)
{
	if (chdir(path) == -1)
	{
		error(sh, "cd", ft_strjoin(path, ": No such file or directory"), 1);
		sh->status = 1;
		return ;
	}
	if (replace_envp(sh) == 1)
	{
		sh->status = 1;
	}
	else
	{
		sh->status = 0;
	}
}

void cd(t_shell *sh, char **args)
{
	char	*w_dir;
	char	*new_pwd;
	
	if (args[1] && args[2])
	{
		error(sh, "cd", "too many arguments", 1);
		sh->status = 1;
		return;
	}
	w_dir = getcwd(NULL, 0);
	if (w_dir == NULL)
	{
		error(sh, "cd", "getcwd error", 1);
		sh->status = 1;
		return ;
	}
	new_pwd = NULL;
	if (is_full_path(sh, args[1], &new_pwd))
	{
		sh->status = 1;
		return ;
	}
	move(new_pwd, sh);
	free(new_pwd);
	return (free(w_dir));
}
