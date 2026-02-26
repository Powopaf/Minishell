/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:07:25 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/26 01:40:21 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../error/err.h"
#include "exec_utils.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t	try_fork(t_shell *sh)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		error(sh, "fork", strerror(errno), -EXIT_FAILURE);
	}
	return (pid);
}

int	try_pipe(t_shell *sh, int fd[2])
{
	if (pipe(fd) < 0)
	{
		error(sh, "pipe", strerror(errno), -EXIT_FAILURE);
		return (0);
	}
	return (1);
}

int	restore_std(t_shell *sh)
{
	if (dup2(sh->stdin_fd, STDIN_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), -EXIT_FAILURE);
		return (0);
	}
	if (dup2(sh->stdout_fd, STDOUT_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), -EXIT_FAILURE);
		return (0);
	}
	return (1);
}

int	wait_ast(t_ast *node)
{
	int	status;
	int	exit_status;

	exit_status = node->shell->status;
	if (!node)
		return (exit_status);
	if (node->left && node)
		status = wait_ast(node->left);
	if (node->right)
		status = wait_ast(node->right);
	if (node->astkw == AST_SUBSHELL)
		exit_status = node->status;
	else if (node->astkw == AST_CMD && node->pid == -1)
		exit_status = node->status;
	else if (node->pid > 0)
	{
			waitpid(node->pid, &status, 0);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status) + SIG_BASE;
	}
	return (exit_status);
}

int	is_dir(char *path)
{
	struct stat	status;

	if (!path)
		return (0);
	if (stat(path, &status) == -1)
		return (0);
	return (S_ISDIR(status.st_mode));
}
