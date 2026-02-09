/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:08:31 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/11 14:39:41 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_utils.h"
#include <sys/wait.h>
#include <stdlib.h>
#include "../error/err.h"
#include "../clean/clean_shell.h"
#include "../signal/signal_handling.h"

static int  exec_sub(t_shell *sh, t_ast *node);
static int  exec_pipe(t_shell *sh, t_ast *node);
static int exec_logop(t_shell *sh, t_ast *node);

static int	exec(t_shell *sh, t_ast *node)
{
	if (!node)
		return (EXIT_SUCCESS);
	if (node->astkw == AST_CMD)
		return (exec_cmd(sh, node));
	if (node->astkw == AST_PIPE)
		return (exec_pipe(sh, node));
	if (node->astkw == AST_AND || node->astkw == AST_OR)
		return (exec_logop(sh, node));
	if (node->astkw == AST_SUBSHELL)
		return (exec_sub(sh, node));
	return (EXIT_FAILURE);
}

static int	exec_sub(t_shell *sh, t_ast *node)
{
	int	status;

	status = EXIT_FAILURE;
	node->pid = try_fork(sh);
	if (node->pid < 0)
		return (EXIT_FAILURE);
	if (node->pid == 0)
	{
		setup_child_signals(sh);
		status = exec_root(sh, node->left);
		clean_shell(sh);
		exit(status);
	}
	ignore_signals();
	waitpid(node->pid, &node->status, 0);
	setup_signals(sh);
	if (WIFEXITED(node->status))
		node->status = WEXITSTATUS(node->status);
	else if (WIFSIGNALED(node->status))
		node->status = WTERMSIG(node->status) + SIG_BASE;
	return (status);
}

static int	exec_pipe(t_shell *sh, t_ast *node)
{
	pid_t	pid_left;
	pid_t	pid_right;

	if (!node->left || !node->right)
		return (EXIT_FAILURE);
	if (setup_pipe(sh, node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pid_left = exec(sh, node->left);
	if (sh->exit != -1)
		return (sh->exit);
	if (pid_left == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pid_right = exec(sh, node->right);
	if (sh->exit != -1)
		return (sh->exit);
	if (pid_right == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	exec_logop(t_shell *sh, t_ast *node)
{
	int	left_status;

	if (!node)
		return (EXIT_FAILURE);
	left_status = exec(sh, node->left);
	if (sh->exit != -1)
		return (sh->exit);
	if (node->astkw == AST_AND)
	{
		if (left_status == EXIT_SUCCESS)
			return (exec(sh, node->right));
		return (left_status);
	}
	else if (node->astkw == AST_OR)
	{
		if (left_status != EXIT_SUCCESS)
			return (exec(sh, node->right));
		return (left_status);
	}
	return (EXIT_FAILURE);
}

int	exec_root(t_shell *sh, t_ast *node)
{
	int	status;

	status = -1;
	if (!node)
		return (EXIT_SUCCESS);
	if (node->astkw == AST_CMD)
		status = exec_cmd(sh, node);
	if (node->astkw == AST_PIPE)
		status = exec_pipe(sh, node);
	if (node->astkw == AST_AND || node->astkw == AST_OR)
		status = exec_logop(sh, node);
	if (node->astkw == AST_SUBSHELL)
		status = exec_sub(sh, node);
	if (status == -1)
		return (EXIT_FAILURE);
	sh->status = wait_ast(node);
	setup_signals(sh);
	return (sh->status);
}
