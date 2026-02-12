/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:12:07 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/12 15:17:33 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean_shell.h"
#include <stdlib.h>
#include <unistd.h>
#include "../../libft/libft.h"

static void	clean_ast(t_ast	*node)
{
	if (!node)
		return ;
	ft_free_array_strs(&node->args);
	redir_clear(&node->redir, clean_redir);
	ft_close_fd(&node->fd_in);
	ft_close_fd(&node->fd_out);
	free(node);
}

static void	ast_clear(t_ast **ast, void (*del)(t_ast	*))
{
	if (!ast || !*ast)
		return ;
	if ((*ast)->left)
		ast_clear(&(*ast)->left, del);
	if ((*ast)->right)
		ast_clear(&(*ast)->right, del);
	del(*ast);
	*ast = NULL;
}

static void	clean_token(t_token	*tk)
{
	if (tk && tk->token)
	{
		free(tk->token);
		tk->token = NULL;
	}
}

void	clean_shell(t_shell *shell)
{
	ft_free_array_strs(&shell->envp);
	ft_close_fd(&shell->stdin_fd);
	ft_close_fd(&shell->stdout_fd);
	ft_close_fd(&shell->hd_fd);
	if (shell->file)
		free(shell->file);
	free(shell->name);
	free(shell->line);
	tokens_clear(&shell->tokens, clean_token);
	ast_clear(&shell->ast, clean_ast);
}

void	clean_prompt(t_shell *shell)
{
	ft_close_fd(&shell->hd_fd);
	if (shell->file)
	{
		free(shell->file);
		shell->file = NULL;
	}
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	tokens_clear(&shell->tokens, clean_token);
	ast_clear(&shell->ast, clean_ast);
}
