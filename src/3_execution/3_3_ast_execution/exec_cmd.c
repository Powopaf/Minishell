/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:43:29 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/02 14:57:19 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/2_parsing_ast/heredoc.h"
#include "./src/3_execution/3_1_expansion/expand.h"
#include "./src/3_execution/3_2_cmd_parsing/parser_cmd.h"
#include "./src/3_execution/3_3_ast_execution/exec_utils.h"
#include "./src/4_builtin_functions/func.h"
#include "./src/5_signal_handling/signal_handling.h"
#include "./src/6_cleaning/clean_shell.h"
#include "./src/7_error_handling/err.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	pipe_redir(t_shell *sh, t_ast *node)
{
	if (node->fd_in > -1 && dup2(node->fd_in, STDIN_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), FAIL);
		return (0);
	}
	if (node->fd_out > -1 && dup2(node->fd_out, STDOUT_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), FAIL);
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

	cmd = NULL;
	args = NULL;
	envp = NULL;
	cmd = parse_cmd(sh, node);
	if (!cmd)
		clean_exit_forked_cmd(node, cmd, args, envp);
	args = ft_strsdup(node->args);
	if (!args)
		return (error(sh, "malloc", strerror(errno), -FAIL),
			clean_exit_forked_cmd(node, cmd, args, envp));
	envp = ft_strsdup(sh->envp);
	if (!envp)
		return (error(sh, "malloc", strerror(errno), -FAIL),
			clean_exit_forked_cmd(node, cmd, args, envp));
	if (is_builtin(sh, node, args, cmd) > 0)
		clean_exit_forked_cmd(node, cmd, args, envp);
	clean_shell(sh);
	execve(cmd, args, envp);
	error(sh, node->args[0], strerror(errno), FAIL);
}

static void	exec_forked(t_shell *sh, t_ast *node)
{
	setup_child_signals(sh);
	if (!pipe_redir(sh, node))
		exit(FAIL);
	if (!redir(sh, node->redir))
		exit(FAIL);
	exec_bin(sh, node);
}

void	exec_cmd(t_shell *sh, t_ast *node)
{
	if (!node)
		return ;
	expand_cmd(sh, node);
	handle_heredocs(sh, node);
	if (node->args && node->args[0] && (!node->parent
			|| node->parent->astkw != AST_PIPE))
	{
		if (is_builtin_main(sh, node, node->args, node->args[0]))
			return (ft_close_fd(&node->fd_in), ft_close_fd(&node->fd_out));
	}
	node->pid = try_fork(sh);
	if (node->pid < 0)
		return ;
	if (node->pid == 0)
		exec_forked(sh, node);
	return (ignore_signals(), ft_close_fd(&node->fd_in),
		ft_close_fd(&node->fd_out));
}
