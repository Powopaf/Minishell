/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:02:15 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/04 18:11:58 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"
#include "../error/err.h"
#include <errno.h>
#include <unistd.h>

char	**ft_parse_path(t_shell *sh, t_ast *node)
{
	char	*path;
	char	**paths;

	path = ft_collect_env_var(sh, "PATH");
	if (!path)
		error(sh, node->args[0], strerror(errno), CMD_NOT_FND);
	paths = ft_split(path, ':');
	free(path);
	if (!paths)
		error(sh, "malloc", MALLOC_ERR, EXIT_FAILURE);
	return (paths);
}

int	ft_check_exec_rights(t_shell *sh, t_ast *node, char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (EXIT_SUCCESS);
		else
		{
			if (ft_isdir(cmd))
			{
				free(cmd);
				error(sh, node->args[0], ISDIR, CMD_PERM_DND);
			}
			free(cmd);
			error(sh, node->args[0], strerror(errno), CMD_PERM_DND);
		}
	}
	return (EXIT_FAILURE);
}

char	*ft_search_cmd(t_shell *sh, t_ast *node)
{
	char	**paths;
	char	*full_cmd;

	paths = ft_parse_path(sh, node);
	if (!paths)
		return (NULL);
	while (*paths)
	{
		full_cmd = ft_strjoin(*paths, "/");
		full_cmd = ft_strjoin_free(&full_cmd, &node->args[0], 1);
		if (!full_cmd)
		{
			ft_empty_array_strs(paths);
			ft_error(sh, "malloc", MALLOC_ERR, EXIT_FAILURE);
		}
		if (ft_check_exec_rights(sh, node, full_cmd) == EXIT_SUCCESS)
		{
			ft_empty_array_strs(paths);
			return (full_cmd);
		}
		free(full_cmd);
		paths++;
	}
	ft_empty_array_strs(paths);
	error(sh, node->args[0], strerror(errno), CMD_NOT_FND);
	return (NULL);
}

char	*ft_local_cmd(t_shell *sh, t_ast *node)
{
	char	*cmd;

	cmd = NULL;
	if (access(node->args[0], F_OK))
	{
		error(sh, node->args[0], strerror(errno), CMD_NOT_FND);
		return (NULL);
	}
	if (ft_isdir(node->args[0]))
	{
		error(sh, node->args[0], ISDIR, CMD_PERM_DND);
		return (NULL);
	}
	if (access(node->args[0], X_OK))
	{
		error(sh, node->args[0], strerror(errno), CMD_PERM_DND);
		return (NULL);
	}
	cmd = ft_strdup(node->args[0]);
	if (!cmd)
		error(sh, "malloc", MALLOC_ERR, EXIT_FAILURE);
	return (cmd);
}

char	*ft_parse_cmd(t_shell *sh, t_ast *node)
{
	char	*cmd;

	cmd = NULL;
	if (ft_strchr(node->args[0], '/'))
		cmd = ft_local_cmd(sh, node);
	else
		cmd = ft_search_cmd(sh, node);
	return (cmd);
}
