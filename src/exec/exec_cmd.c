/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:43:29 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/06 15:32:28 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_cmd/parser_cmd.h"
#include "exec_utils.h"
#include "../error/err.h"
#include "../clean/clean_shell.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../../libft/libft.h"

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
	close(node->fd_in);
	close(node->fd_out);
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
	clean_shell(sh);
	execve(cmd, args, envp);
	error(sh, node->args[0], strerror(errno), EXIT_FAILURE);
}

int	exec_cmd(t_shell *sh, t_ast *node)
{
	if (!node)
		return (EXIT_SUCCESS);
	// if (!node->args || !*(node->args))
	// {
	// 	int check = ft_redir(sh, node->redir);
	// 	ft_restore_std(sh);
	// 	if (check != SUCCESS)
	// 		return (FAIL);
	// 	return (SUCCESS);
	// }
	// built-in?
	node->pid = try_fork(sh);
	if (node->pid < 0)
	{
		error(sh, "fork", strerror(errno), -EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (node->pid == 0)
	{
		// signal ??
		if (pipe_redir(sh, node) != EXIT_SUCCESS)
			exit(EXIT_FAILURE);
		if (redir(sh, node->redir) != EXIT_SUCCESS)
			exit(EXIT_FAILURE);
		exec_bin(sh, node);
	}
	close(node->fd_in);
	close(node->fd_out);
	return (EXIT_SUCCESS);
}
