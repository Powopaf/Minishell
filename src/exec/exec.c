/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:08:31 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/25 19:52:10 by flomulle         ###   ########.fr       */
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
		exec_root(sh, node->left);
		clean_shell(sh);
		exit(sh->status);
	}
	ignore_signals();
	waitpid(node->pid, &node->status, 0);
	setup_signals(sh);
	if (WIFEXITED(node->status))
		node->status = WEXITSTATUS(node->status);
	else if (WIFSIGNALED(node->status))
		node->status = WTERMSIG(node->status) + SIG_BASE;
	return ;
}

static void	exec_pipe(t_shell *sh, t_ast *node)
{
	if (!node->left || !node->right)
		return ;
	if (!setup_pipe(sh, node))
		return ;
	exec(sh, node->left);
	if (sh->exit != -1)
		return ;
	exec(sh, node->right);
	if (sh->exit != -1)
		return ;
	return ;
}

static void	exec_logop(t_shell *sh, t_ast *node)
{
	if (!node)
		return ;
	exec(sh, node->left);
	sh->status = wait_ast(node->left);
	if (sh->exit != -1)
		return ;
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
