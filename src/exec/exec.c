/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:08:31 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/26 23:34:33 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../clean/clean_shell.h"
#include "../error/err.h"
#include "../signal/signal_handling.h"
#include "exec.h"
#include "exec_utils.h"
#include <stdlib.h>
#include <sys/wait.h>

static void	exec_sub(t_shell *sh, t_ast *node);
static void	exec_pipe(t_shell *sh, t_ast *node);
static void	exec_logop(t_shell *sh, t_ast *node);

static void	exec(t_shell *sh, t_ast *node)
{
	if (!node)
		return ;
	if (node->astkw == AST_CMD)
		exec_cmd(sh, node);
	if (node->astkw == AST_PIPE)
		exec_pipe(sh, node);
	if (node->astkw == AST_AND || node->astkw == AST_OR
		|| node->astkw == AST_THEN)
		exec_logop(sh, node);
	if (node->astkw == AST_SUBSHELL)
		exec_sub(sh, node);
	return ;
}

static void	exec_sub(t_shell *sh, t_ast *node)
{
	node->pid = try_fork(sh);
	if (node->pid < 0)
		return ;
	if (node->pid == 0)
	{
		setup_child_signals(sh);
		if (!pipe_redir(sh, node))
			exit(EXIT_FAILURE);
		if (!redir(sh, node->redir))
			exit(EXIT_FAILURE);
		exec_root(sh, node->left);
		clean_shell(sh);
		exit(sh->status);
	}
	ignore_signals();
	sh->status = wait_pid(node);
	setup_signals(sh);
	return ;
}

static void	exec_pipe(t_shell *sh, t_ast *node)
{
	if (!node->left || !node->right)
		return ;
	if (!setup_pipe(sh, node))
		return ;
	exec(sh, node->left);
	exec(sh, node->right);
	return ;
}

static void	exec_logop(t_shell *sh, t_ast *node)
{
	if (!node)
		return ;
	exec(sh, node->left);
	sh->status = wait_ast(node->left);

	if (node->astkw == AST_AND)
	{
		if (sh->status == EXIT_SUCCESS)
			return (exec(sh, node->right));
		return ;
	}
	else if (node->astkw == AST_OR)
	{
		if (sh->status != EXIT_SUCCESS)
			return (exec(sh, node->right));
		return ;
	}
	else if (node->astkw == AST_THEN)
		return (exec(sh, node->right));
	return ;
}

void	exec_root(t_shell *sh, t_ast *node)
{
	if (!node)
	{
		sh->status = 0;
		return ;
	}
	if (node->astkw == AST_CMD)
		exec_cmd(sh, node);
	if (node->astkw == AST_PIPE)
		exec_pipe(sh, node);
	if (node->astkw == AST_AND || node->astkw == AST_OR
		|| node->astkw == AST_THEN)
		exec_logop(sh, node);
	if (node->astkw == AST_SUBSHELL)
		exec_sub(sh, node);
	sh->status = wait_ast(node);
	setup_signals(sh);
}
