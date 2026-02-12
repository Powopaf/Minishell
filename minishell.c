/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:12:40 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/12 10:43:22 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "src/init/init_shell.h"
#include <readline/history.h>
#include "src/parsing/token/tokens.h"
#include "src/parsing/token/syntax/syntax.h"
#include "src/exec/exec.h"
#include <stdio.h>
#include "src/parsing/expend/expand.h"
#include "src/parsing/parsing.h"
#include "src/clean/clean_shell.h"
#include "signal.h"
#include "src/signal/signal_handling.h"

volatile sig_atomic_t	g_signal = 0;

static int	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;

	if (!*line)
		return (EXIT_FAILURE);
	if (g_signal == SIGINT)
	{
		shell->status = SIGINT_STATUS;
		g_signal = 0;
	}
	add_history(line);
	shell->line = line;
	if (tokenization(shell))
		return (EXIT_FAILURE);
	if (check_syntax(shell))
		return (EXIT_FAILURE);
	tokens = shell->tokens;
	shell->ast = parser(shell, &tokens);
	if (!shell->ast)
		return (EXIT_FAILURE);
	expand_var(shell, shell->ast);
	shell->status = exec_root(shell, shell->ast);
	clean_prompt(shell);
	return (shell->exit != -1);
}

static void	shell_process(t_shell *shell)
{
	char	*line;

	while (1)
	{
		setup_signals(shell);
		line = readline(shell->name);
		if (!line)
		{
			if (shell->tty)
				printf("exit\n");
			break ;
		}
		shell->line_cnt++;
		if (process_line(shell, line))
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	initialize_shell(&shell, envp, argv);
	shell_process(&shell);
	clean_shell(&shell);
	rl_clear_history();
	if (shell.exit == -1)
		return (shell.status);
	return (shell.exit);
}
