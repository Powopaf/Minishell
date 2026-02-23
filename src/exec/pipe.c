/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:22:29 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/23 15:07:39 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"
#include "../error/err.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "../../libft/libft.h"

static int	pipe_right(t_shell *sh, t_ast *node, int fd)
{
	t_ast	*tmp;

	tmp = node->right;
	while (tmp->astkw != AST_CMD)
	{
		if (tmp->left)
		{
			tmp = tmp->left;
			continue ;
		}
		if (tmp->right)
		{
			tmp = tmp->right;
			continue ;
		}
		error(sh, DEBUG, DEBUG, -EXIT_FAILURE);
		return (0);
	}
	ft_close_fd(&tmp->fd_in);
	tmp->fd_in = fd;
	return (1);
}

static int	pipe_left(t_shell *sh, t_ast *node, int fd)
{
	t_ast	*tmp;

	tmp = node->left;
	while (tmp->astkw != AST_CMD)
	{
		if (tmp->right)
		{
			tmp = tmp->right;
			continue ;
		}
		if (tmp->left)
		{
			tmp = tmp->left;
			continue ;
		}
		error(sh, DEBUG, DEBUG, -EXIT_FAILURE);
		return (0);
	}
	ft_close_fd(&tmp->fd_out);
	tmp->fd_out = fd;
	return (1);
}

int	setup_pipe(t_shell *sh, t_ast *node)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		error(sh, "pipe", strerror(errno), -EXIT_FAILURE);
		return (0);
	}
	if (!pipe_left(sh, node, fd[1]))
		return (0);
	if (!pipe_right(sh, node, fd[0]))
		return (0);
	return (1);
}
