/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:59:25 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/22 23:25:01 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../error/err.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "exec_utils.h"
#include <string.h>
#include "../../libft/libft.h"

static int	redir_hd(t_shell *sh, t_redir *redir)
{
	if (redir->fd_in < 0)
		return (0);
	if (dup2(redir->fd_in, STDIN_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), EXIT_FAILURE);
		return (0);
	}
	return (1);
}

static int	redir_in(t_shell *sh, t_redir *redir)
{
	ft_close_fd(&redir->fd_in);
	redir->fd_in = open(redir->file, O_RDONLY);
	if (redir->fd_in < 0)
	{
		error(sh, redir->file, strerror(errno), EXIT_FAILURE);
		return (0);
	}
	if (dup2(redir->fd_in, STDIN_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), EXIT_FAILURE);
		return (0);
	}
	return (1);
}

static int	redir_out(t_shell *sh, t_redir *redir)
{
	ft_close_fd(&redir->fd_out);
	redir->fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (redir->fd_out < 0)
	{
		error(sh, redir->file, strerror(errno), EXIT_FAILURE);
		return (0);
	}
	if (dup2(redir->fd_out, STDOUT_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), EXIT_FAILURE);
		return (0);
	}
	return (1);
}

static int	redir_app(t_shell *sh, t_redir *redir)
{
	ft_close_fd(&redir->fd_out);
	redir->fd_out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (redir->fd_out < 0)
	{
		error(sh, redir->file, strerror(errno), EXIT_FAILURE);
		return (0);
	}
	if (dup2(redir->fd_out, STDOUT_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), EXIT_FAILURE);
		return (0);
	}
	return (1);
}

int	redir(t_shell *sh, t_redir *redir)
{
	while (redir)
	{
		if (redir->kw == REDIR_HD)
		{
			if (!redir_hd(sh, redir))
				return (0);
		}
		else if (redir->kw == REDIR_IN)
		{
			if (!redir_in(sh, redir))
				return (0);
		}
		else if (redir->kw == REDIR_OUT)
		{
			if (!redir_out(sh, redir))
				return (0);
		}
		else if (redir->kw == REDIR_APP)
		{
			if (!redir_app(sh, redir))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}
