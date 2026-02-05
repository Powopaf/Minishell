/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:12:40 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/04 18:41:21 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
# include <readline/readline.h>
#include "minishell.h"
#include "src/init/init_shell.h"
#include <readline/history.h>
#include "src/token/tokens.h"
#include "src/token/syntax/syntax.h"

static int	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;

	if (!*line)
		return (EXIT_FAILURE);
	// signal
	add_history(line);
	shell->l = line;
	if (tokenization(shell))
		return (EXIT_FAILURE);
	if (check_syntax(shell))
		return (EXIT_FAILURE);
	tokens = shell->tokens;
	shell->ast = ft_parse(shell, &tokens);
	if (!shell->ast)
		return (EXIT_FAILURE);
	ft_expand_variables(shell, shell->ast);
	shell->status = ft_execute_root(shell, shell->ast);
	ft_clean_prompt(shell);
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
	ft_clean_prompt(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	(void)argc;

	initialize_shell(&shell, envp, argv);
	shell_process(&shell);
	ft_clean_shell(&shell);
	rl_clear_history();
	return (shell.status);
}
