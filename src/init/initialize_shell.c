/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:46:22 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/05 13:22:48 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../struct.h"
#include "../error/err.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

static void	ft_copy_envp(t_shell *shell, char **envp)
{
	if (!envp)
	{
		shell->envp = (char **)malloc(sizeof(*shell->envp));
		if (!shell->envp)
			error(shell, "malloc", MALLOC_ERR, FAIL);
		shell->envp[0] = NULL;
		return ;
	}
	shell->envp = ft_strsdup(envp);
	if (!shell->envp)
		error(shell, "malloc", MALLOC_ERR, FAIL);
}

void	ft_initialize_shell(t_shell *shell, char **envp)
{
	ft_copy_envp(shell, envp);
	shell->status = 0;
	shell->stdin_fd = dup(STDIN_FILENO);
	if (shell->stdin_fd == -1)
		error(shell, "dup", strerror(errno), FAIL);
	shell->stdout_fd = dup(STDOUT_FILENO);
	if (shell->stdout_fd == -1)
		error(shell, "dup", strerror(errno), FAIL);
	shell->hd_fd = -1;
	shell->file = NULL;
	shell->cmd_cnt = 0;
	shell->l = NULL;
	shell->tokens = NULL;
	shell->ast = NULL;
	//ft_init_terminal(shell);
	//ft_setup_signals(shell);
}
