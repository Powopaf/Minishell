/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:22:29 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/02 23:43:40 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/3_execution/3_3_ast_execution/exec_utils.h"
#include "./src/7_error_handling/err.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

static int	pipe_right(t_shell *sh, t_ast *node, int fd)
{
	t_ast	*tmp;

	(void)sh;
	tmp = node->right;
	while (tmp->astkw != AST_CMD && tmp->astkw != AST_SUBSHELL)
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
		return (0);
	}
	ft_close_fd(&tmp->fd_in);
	tmp->fd_in = fd;
	return (1);
}

static int	pipe_left(t_shell *sh, t_ast *node, int fd)
{
	t_ast	*tmp;

	(void)sh;
	tmp = node->left;
	while (tmp->astkw != AST_CMD && tmp->astkw != AST_SUBSHELL)
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
		error(sh, "pipe", strerror(errno), -FAIL);
		return (0);
	}
	if (!pipe_left(sh, node, fd[1]))
		return (0);
	if (!pipe_right(sh, node, fd[0]))
		return (0);
	return (1);
}
