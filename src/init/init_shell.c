/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:46:22 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/12 16:35:51 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../struct.h"
#include "../error/err.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../libft/libft.h"
#include "init_shell.h"
#include "../signal/signal_handling.h"

static void	init_terminal(t_shell *shell)
{
	if (isatty(STDIN_FILENO))
	{
		shell->tty = 1;
		tcgetattr(STDIN_FILENO, &shell->original_termios);
	}
	else
		shell->tty = 0;
}

static void	copy_envp(t_shell *shell, char **envp)
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

static void	get_shell_name(t_shell *shell, char **argv)
{
	if (!argv || !*argv)
	{
		shell->name = "minishell> ";
		return ;
	}
	shell->name = ft_strrchr(*argv, '/');
	shell->name = ft_strjoin(*argv, PROMPT_HD);
}

void	initialize_shell(t_shell *shell, char **envp, char **argv)
{
	copy_envp(shell, envp);
	shell->status = 0;
	shell->stdin_fd = dup(STDIN_FILENO);
	if (shell->stdin_fd == -1)
		error(shell, "dup", strerror(errno), FAIL);
	shell->stdout_fd = dup(STDOUT_FILENO);
	if (shell->stdout_fd == -1)
		error(shell, "dup", strerror(errno), FAIL);
	shell->hd_fd = -1;
	shell->file = NULL;
	shell->line_cnt = 0;
	shell->line = NULL;
	shell->tokens = NULL;
	shell->ast = NULL;
	get_shell_name(shell, argv);
	shell->exit = -1;
	init_terminal(shell);
	setup_signals(shell);
}
