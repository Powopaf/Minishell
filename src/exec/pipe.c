/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:22:29 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/06 15:24:46 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"
#include "../error/err.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>

static int pipe_right(t_shell *sh, t_ast *node, int fd)
{
	t_ast *tmp;
	tmp = node->right;
	while (tmp->astkw != AST_CMD)
	{
		if (tmp->left)
		{
			tmp = tmp->left;
			continue;
		}
		if (tmp->right)
		{
			tmp = tmp->right;
			continue;
		}
		error(sh, DEBUG, DEBUG, -EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	close(tmp->fd_in);
	tmp->fd_in = fd;
	return (EXIT_SUCCESS);
}

static int pipe_left(t_shell *sh, t_ast *node, int fd)
{
	t_ast *tmp;

	tmp = node->left;
	while (tmp->astkw != AST_CMD)
	{
		if (tmp->right)
		{
			tmp = tmp->right;
			continue;
		}
		if (tmp->left)
		{
			tmp = tmp->left;
			continue;
		}
		error(sh, DEBUG, DEBUG, -EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	close(tmp->fd_out);
	tmp->fd_out = fd;
	return (EXIT_SUCCESS);
}

int	setup_pipe(t_shell *sh, t_ast *node)
{
	int	fd[2];
	if (pipe(fd) == -1)
	{
		error(sh, "pipe", strerror(errno), -EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (pipe_left(sh, node, fd[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pipe_right(sh, node, fd[0]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
