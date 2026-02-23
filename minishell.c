/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:12:40 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/23 00:09:16 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "src/0_init/init_shell.h"
#include <readline/history.h>
#include "src/1_tokenization/tokens.h"
#include "src/1_tokenization/syntax/syntax.h"
#include "src/exec/exec.h"
#include <stdio.h>
#include "src/2_parsing_ast/parsing.h"
#include "src/clean/clean_shell.h"
#include "signal.h"
#include "src/signal/signal_handling.h"
#include "./libft/libft.h"

volatile sig_atomic_t	g_signal = 0;

static int	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;

	if (!*line)
		return (0);
	if (g_signal == SIGINT)
	{
		shell->status = SIGINT_STATUS;
		g_signal = 0;
	}
	shell->line = line;
	if (!tokenization(shell))
		return (clean_prompt(shell), 0);
	if (!check_syntax(shell))
		return (clean_prompt(shell), 0);
	tokens = shell->tokens;
	shell->ast = parser(shell, &tokens);
	if (!shell->ast)
		return (clean_prompt(shell), 0);
	exec_root(shell, shell->ast);
	clean_prompt(shell);
	return (shell->exit != -1);
}

static void	shell_process_non_tty(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = ft_get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		trim_newline(line);
		shell->line_cnt++;
		if (process_line(shell, line))
			break ;
	}
}

static void	shell_process_tty(t_shell *shell)
{
	char	*line;

	while (1)
	{
		setup_signals(shell);
		line = readline(shell->name);
		if (!line)
		{
			write(2, "exit\n", 5);
			break ;
		}
		add_history(line);
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
	if (shell.tty)
		shell_process_tty(&shell);
	else
		shell_process_non_tty(&shell);
	clean_shell(&shell);
	rl_clear_history();
	if (shell.exit == -1)
		return (shell.status);
	return (shell.exit);
}
