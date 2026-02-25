/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:02:15 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/25 14:00:02 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../../error/err.h"
#include "../exec_utils.h"
#include "parser_cmd.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char	**parse_path(t_shell *sh, t_ast *node)
{
	char	*path;
	char	**paths;

	path = get_env(sh, "PATH");
	if (!path)
		error(sh, node->args[0], strerror(errno), CMD_NOT_FND);
	paths = ft_split(path, ':');
	free(path);
	if (!paths)
		error(sh, "malloc", strerror(errno), FAIL);
	return (paths);
}

static int	check_bin_rights(t_shell *sh, t_ast *node, char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (1);
		else
		{
			if (is_dir(cmd))
			{
				free(cmd);
				error(sh, node->args[0], ISDIR, CMD_PERM_DND);
			}
			free(cmd);
			error(sh, node->args[0], strerror(errno), CMD_PERM_DND);
		}
	}
	return (0);
}

static char	*search_cmd(t_shell *sh, t_ast *node)
{
	char	**paths;
	char	*full_cmd;
	size_t	i;

	i = -1;
	paths = parse_path(sh, node);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		full_cmd = ft_strjoin(paths[i], "/");
		full_cmd = ft_strjoin_free(&full_cmd, &node->args[0], 1);
		if (!full_cmd)
		{
			ft_empty_array_strs(paths);
			error(sh, "malloc", strerror(errno), FAIL);
		}
		if (check_bin_rights(sh, node, full_cmd))
		{
			return (ft_empty_array_strs(paths), full_cmd);
		}
		free(full_cmd);
	}
	ft_empty_array_strs(paths);
	return (error(sh, node->args[0], CMD_NOT_FND_ERR, CMD_NOT_FND), NULL);
}

static char	*local_cmd(t_shell *sh, t_ast *node)
{
	char	*cmd;

	cmd = NULL;
	if (access(node->args[0], F_OK))
	{
		error(sh, node->args[0], strerror(errno), CMD_NOT_FND);
	}
	if (is_dir(node->args[0]))
	{
		error(sh, node->args[0], ISDIR, CMD_PERM_DND);
	}
	if (access(node->args[0], X_OK))
	{
		error(sh, node->args[0], strerror(errno), CMD_PERM_DND);
	}
	cmd = ft_strdup(node->args[0]);
	if (!cmd)
		error(sh, "malloc", strerror(errno), FAIL);
	return (cmd);
}

char	*parse_cmd(t_shell *sh, t_ast *node)
{
	char	*cmd;

	cmd = NULL;
	if (!node || !node->args || !node->args[0])
		return (NULL);
	if (!node->args[0][0])
		return (error(sh, node->args[0], CMD_NOT_FND_ERR, CMD_NOT_FND), NULL);
	if (ft_strncmp(node->args[0], "echo", 5) == 0 || ft_strncmp(node->args[0],
			"cd", 3) == 0 || ft_strncmp(node->args[0], "pwd", 4) == 0
		|| ft_strncmp(node->args[0], "export", 7) == 0
		|| ft_strncmp(node->args[0], "unset", 6) == 0
		|| ft_strncmp(node->args[0], "env", 4) == 0 || ft_strncmp(node->args[0],
			"exit", 5) == 0)
	{
		cmd = ft_strdup(node->args[0]);
		return (cmd);
	}
	if (ft_strchr(node->args[0], '/'))
		cmd = local_cmd(sh, node);
	else
		cmd = search_cmd(sh, node);
	return (cmd);
}
