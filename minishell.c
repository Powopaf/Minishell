/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:12:40 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/06 14:43:03 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <readline/readline.h>
#include "src/init/init_shell.h"
#include <readline/history.h>
#include "src/parsing/token/tokens.h"
#include "src/parsing/token/syntax/syntax.h"
#include "src/exec/exec.h"
#include <stdio.h>
#include "src/parsing/expend/expand.h"
#include "src/parsing/parsing.h"
#include "src/clean/clean_shell.h"

static int	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;

	if (!*line)
		return (EXIT_FAILURE);
	// signal
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
	return (EXIT_SUCCESS);
}

static void	shell_process(t_shell *shell)
{
	char	*line;

//	ft_signals();
	while (1)
	{
		line = readline(shell->name);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (process_line(shell, line))
			break ;
	}
	clean_prompt(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	(void)argc;

	initialize_shell(&shell, envp, argv);
	shell_process(&shell);
	clean_shell(&shell);
	rl_clear_history();
	return (shell.status);
}
