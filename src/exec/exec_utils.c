/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:07:25 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/06 15:52:49 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"
#include <errno.h>
#include <unistd.h>
#include "../error/err.h"
#include <string.h>
#include <sys/wait.h>

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
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	restore_std(t_shell *sh)
{
	if (dup2(sh->stdin_fd, STDIN_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), -EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (dup2(sh->stdout_fd, STDOUT_FILENO) < 0)
	{
		error(sh, "dup2", strerror(errno), -EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	wait_ast(t_ast *node)
{
	int status;
	int exit;

	exit = EXIT_SUCCESS;
	if (!node)
		return (exit);
	if (node->left)
		status = wait_ast(node->left);
	if (node->right)
		status = wait_ast(node->right);
	if (node->pid > 0)
	{
		waitpid(node->pid, &status, 0);
		if (WIFEXITED(status))
			exit = WEXITSTATUS(status);
	}
	return (exit);
}
