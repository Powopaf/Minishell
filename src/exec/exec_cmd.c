/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:43:29 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/17 10:29:16 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../clean/clean_shell.h"
#include "../error/err.h"
#include "../func/func.h"
#include "../signal/signal_handling.h"
#include "exec_utils.h"
#include "parser_cmd/parser_cmd.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	pipe_redir(t_shell *sh, t_ast *node)
{
	if (node->fd_in > -1 && dup2(node->fd_in, STDIN_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (node->fd_out > -1 && dup2(node->fd_out, STDOUT_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	ft_close_fd(&node->fd_in);
	ft_close_fd(&node->fd_out);
	return (EXIT_SUCCESS);
}

static void	exec_bin(t_shell *sh, t_ast *node)
{
	char	*cmd;
	char	**args;
	char	**envp;

	cmd = parse_cmd(sh, node);
	args = ft_strsdup(node->args);
	if (!args)
		error(sh, "malloc", MALLOC_ERR, EXIT_FAILURE);
	envp = ft_strsdup(sh->envp);
	if (!envp)
		error(sh, "malloc", MALLOC_ERR, EXIT_FAILURE);
	if (is_builtin(cmd, sh, args) > 0)
	{
		ft_free_array_strs(&args);
		ft_free_array_strs(&envp);
		if (ft_strncmp(cmd, "exit", 5) == 0)
			exit(sh->exit);
		exit(sh->status);
	}
	clean_shell(sh);
	execve(cmd, args, envp);
	if (args && args[0])
		error(sh, args[0], strerror(errno), EXIT_FAILURE);
	exit(EXIT_FAILURE);
}

static void	exec_forked(t_shell *sh, t_ast *node)
{
	setup_child_signals(sh);
	if (pipe_redir(sh, node) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	if (redir(sh, node->redir) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	exec_bin(sh, node);
}

int	exec_cmd(t_shell *sh, t_ast *node)
{
	if (!node)
		return (EXIT_SUCCESS);
	if (node->args && node->args[0])
	{
		if (node->fd_in == -1 && node->fd_out == -1 && !node->redir)
		{
			if (is_builtin(node->args[0], sh, node->args) > 0)
			{
				if (ft_strncmp(node->args[0], "exit", 5) == 0)
					return (sh->exit);
				return (sh->status);
			}
		}
	}
	node->pid = try_fork(sh);
	if (node->pid < 0)
		return (error(sh, "fork", strerror(errno),
				-EXIT_FAILURE), EXIT_FAILURE);
	if (node->pid == 0)
		exec_forked(sh, node);
	return (ignore_signals(), ft_close_fd(&node->fd_in),
		ft_close_fd(&node->fd_out), EXIT_SUCCESS);
}
