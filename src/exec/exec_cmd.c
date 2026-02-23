/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:43:29 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/23 15:00:58 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../clean/clean_shell.h"
#include "../error/err.h"
#include "../func/func.h"
#include "../signal/signal_handling.h"
#include "./expand/expand.h"
#include "./heredocs/heredoc.h"
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
		return (0);
	}
	if (node->fd_out > -1 && dup2(node->fd_out, STDOUT_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), EXIT_FAILURE);
		return (0);
	}
	ft_close_fd(&node->fd_in);
	ft_close_fd(&node->fd_out);
	return (1);
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
		if (cmd && ft_strncmp(cmd, "exit", 5) == 0)
			exit(sh->exit);
		exit(sh->status);
	}
	clean_shell(sh);
	if (!cmd)
	{
		ft_free_array_strs(&args);
		ft_free_array_strs(&envp);
		exit(sh->status);
	}
	execve(cmd, args, envp);
	error(sh, node->args[0], strerror(errno), EXIT_FAILURE);
}

static void	exec_forked(t_shell *sh, t_ast *node)
{
	setup_child_signals(sh);
	if (!pipe_redir(sh, node))
		exit(EXIT_FAILURE);
	if (!redir(sh, node->redir))
		exit(EXIT_FAILURE);
	exec_bin(sh, node);
}

void	exec_cmd(t_shell *sh, t_ast *node)
{
	if (!node)
		return ;
	if (!expand_cmd(sh, node))
		return ;
	handle_heredocs(sh, node);
	if (node->args && node->args[0] && (!node->parent
			|| node->parent->astkw != AST_PIPE))
	{
		if (is_builtin(node->args[0], sh, node->args) > 0)
		{
			if (ft_strncmp(node->args[0], "exit", 5) == 0 && sh->exit != -1)
				return ;
			return ;
		}
	}
	node->pid = try_fork(sh);
	if (node->pid < 0)
		return ;
	if (node->pid == 0)
		exec_forked(sh, node);
	return (ignore_signals(), ft_close_fd(&node->fd_in),
		ft_close_fd(&node->fd_out));
}
