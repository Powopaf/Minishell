/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:08:31 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/05 23:08:33 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_utils.h"

int	ft_execute_sub(t_shell *sh, t_ast *node)
{
	int	status;

	ft_printf("Execute subshell\n");
	node->pid = ft_fork(sh);
	if (node->pid < 0)
		return (EXIT_FAILURE);
	if (node->pid == 0)
	{
	// 	// signal ???
		status = ft_execute_root(sh, node->left);
		ft_clean_shell(sh);
		exit(status);
	}
	waitpid(node->pid, &node->status, 0);
	if (WIFEXITED(node->status))
		node->status = WEXITSTATUS(node->status);
	else if (WIFSIGNALED(node->status))
		node->status = WTERMSIG(node->status) + SIG_BASE;
	return (status); // node->status
}

int	ft_execute_pipe(t_shell *sh, t_ast *node)
{
	pid_t	pid_left;
	pid_t	pid_right;

	ft_printf("Execute pipe\n");
	if (!node->left || !node->right)
		return (EXIT_FAILURE);
	if (ft_setup_pipe(sh, node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pid_left = ft_execute(sh, node->left);
	if (pid_left == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pid_right = ft_execute(sh, node->right);
	if (pid_right == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_execute_logop(t_shell *sh, t_ast *node)
{
	int	left_status;

	ft_printf("Execute logop\n");
	if (!node)
		return (EXIT_FAILURE);
	left_status = ft_execute(sh, node->left);
	if (node->astkw == AST_AND)
	{
		if (left_status == EXIT_SUCCESS)
			return (ft_execute(sh, node->right));
		return (left_status);
	}
	else if (node->astkw == AST_OR)
	{
		if (left_status != EXIT_SUCCESS)
			return (ft_execute(sh, node->right));
		return (left_status);
	}
	return (EXIT_FAILURE);
}

int	ft_execute(t_shell *sh, t_ast *node)
{
	if (!node)
		return (EXIT_SUCCESS);
	if (node->astkw == AST_CMD)
		return (ft_execute_cmd(sh, node));
	if (node->astkw == AST_PIPE)
		return (ft_execute_pipe(sh, node));
	if (node->astkw == AST_AND || node->astkw == AST_OR)
		return (ft_execute_logop(sh, node));
	if (node->astkw == AST_SUBSHELL)
		return (ft_execute_sub(sh, node));
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
		status = ft_execute_pipe(sh, node);
	if (node->astkw == AST_AND || node->astkw == AST_OR)
		status = ft_execute_logop(sh, node);
	if (node->astkw == AST_SUBSHELL)
		status = ft_execute_sub(sh, node);
	if (status == -1)
		return (EXIT_FAILURE);
	sh->status = ft_wait(node);
	return (sh->status);
}
