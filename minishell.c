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

#include "minishell.h"

int	ft_process_line(t_shell *shell, char *line)
{
	t_token	*tokens;

	if (!*line)
		return (0);
	// signal
	add_history(line);
	shell->l = line;
ft_printf("=====\n\tStart tokenisation\n=====\n");
	if (!ft_tokenization(shell))// || !ft_tk_syntax(shell))
		return (0);
ft_printf_all(shell);
ft_printf("=====\n\tChecking syntax\n=====\n");
	if (!ft_tk_syntax(shell))
		return (0);
ft_printf("Syntax ok\n");
ft_printf("=====\n\tStart parsing\n=====\n");
	tokens = shell->tokens;
	shell->ast = ft_parse(shell, &tokens);
	if (!shell->ast)
		return (0);
ft_printf_all(shell);
ft_printf("=====\n\tStart expanding\n=====\n");
	ft_expand_variables(shell, shell->ast);
ft_printf_all(shell);
ft_printf("=====\n\tStart execution\n=====\n");
	shell->status = ft_execute_root(shell, shell->ast);
ft_printf("=====\n\tCleaning prompt\n=====\n");
	ft_clean_prompt(shell);
ft_printf("\n\nNEW ENTRY:\n");
	return (1);
}

void	ft_shell_process(t_shell *shell)
{
	char	*line;

//	ft_signals();
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (!ft_process_line(shell, line))
			break ;
	}
	ft_clean_prompt(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	//g_signal = 0;
	ft_initialize_shell(&shell, envp);
ft_printf_all(&shell);
	ft_shell_process(&shell);
	ft_clean_shell(&shell);
	rl_clear_history();
	return (shell.status);
}
