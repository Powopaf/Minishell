/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:55:40 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/02 17:17:41 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src/3_execution/3_3_ast_execution/exec_utils.h"
#include "./src/7_error_handling/err.h"
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int	wait_pid(t_ast *node)
{
	int	status;

	waitpid(node->pid, &status, 0);
	node->pid = -1;
	if (WIFEXITED(status))
		node->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		node->status = WTERMSIG(status) + SIG_BASE;
	return (node->status);
}

int	wait_ast(t_ast *node)
{
	if (node->left)
		node->shell->status = wait_ast(node->left);
	if (node->right)
		node->shell->status = wait_ast(node->right);
	if (node->astkw == AST_CMD && node->pid == -1 && node->status != -1)
		node->shell->status = node->status;
	if (node->pid > 0)
		node->shell->status = wait_pid(node);
	return (node->shell->status);
}
