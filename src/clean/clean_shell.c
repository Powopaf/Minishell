/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:12:07 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/04 18:07:50 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean_shell.h"
#include <stddef.h>

void	ft_clean_ast(t_ast	*node)
{
	if (!node)
		return ;
	ft_free_array_strs(&node->args);
	ft_redir_clear(&node->redir, ft_clean_redir);
	ft_close_fd(&node->fd_in);
	ft_close_fd(&node->fd_out);
	free(node);
}

void	ft_astclear(t_ast **ast, void (*del)(t_ast	*))
{
	if (!ast || !*ast)
		return ;
	if ((*ast)->left)
		ft_astclear(&(*ast)->left, del);
	if ((*ast)->right)
		ft_astclear(&(*ast)->right, del);
	del(*ast);
	*ast = NULL;
}

void	ft_clean_token(t_token	*tk)
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
	ft_free_str(&shell->file);
	ft_free_str(&shell->line);
	ft_tokens_clear(&shell->tokens, ft_clean_token);
	ft_astclear(&shell->ast, ft_clean_ast);
}

void	clean_prompt(t_shell *shell)
{
// ft_printf("Close stdin\n");
// 	ft_close_fd(&shell->stdin_fd);
// ft_printf("Close stdout\n");
// 	ft_close_fd(&shell->stdout_fd);
	ft_close_fd(&shell->hd_fd);
	ft_free_str(&shell->file);
	ft_free_str(&shell->line);
	ft_tokens_clear(&shell->tokens, ft_clean_token);
	ft_astclear(&shell->ast, ft_clean_ast);
}
