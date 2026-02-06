/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:05:36 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/05 23:03:16 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "../../error/err.h"
#include "../../../redir.h"
#include <stdlib.h>
#include <unistd.h>
#include "../../../libft/libft.h"

void	clean_redir(t_redir	*redir)
{
	if (!redir)
		return ;
	// TODO: Check if we can remove the if
	if (redir->file)
		free(redir->file);
	if (redir->eofkw)
		free(redir->eofkw);
	close(redir->fd_in);
	close(redir->fd_out);
	free(redir);
}

void	redir_clear(t_redir **redir, void (*del)(t_redir *))
{
	t_redir	*current;
	t_redir	*redirfree;

	if (!redir || !*redir)
		return ;
	current = *redir;
	while (current)
	{
		redirfree = current;
		current = current->next;
		del(redirfree);
	}
	*redir = NULL;
}

t_ast	*create_ast_node(t_shell *sh, t_ast_node_type astkw)
{
	t_ast	*node;

	node = malloc(sizeof(*node));
	if (!node)
	{
		error(sh, "malloc", MALLOC_ERR, -FAIL);
		return (NULL);
	}
	node->astkw = astkw;
	node->args = NULL;
	node->redir = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->pid = -1;
	node->status = -1;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	ft_clean_ast(t_ast	*node)
{
	if (!node)
		return ;
	ft_free_array_strs(&node->args);
	redir_clear(&node->redir, clean_redir);
	close(node->fd_in);
	close(node->fd_out);
	free(node);
}

void	ast_clear(t_ast **ast, void (*del)(t_ast	*))
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
