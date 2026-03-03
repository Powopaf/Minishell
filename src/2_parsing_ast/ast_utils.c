/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:05:36 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/02 23:29:30 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/2_parsing_ast/ast.h"
#include "./src/7_error_handling/err.h"
#include <stdlib.h>
#include <unistd.h>

t_ast	*create_ast_node(t_shell *sh, t_ast_node_type astkw)
{
	t_ast	*node;

	node = malloc(sizeof(*node));
	if (!node)
	{
		error(sh, "malloc", strerror(errno), -FAIL);
		return (NULL);
	}
	node->astkw = astkw;
	node->args = NULL;
	node->redir = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->ko = 0;
	node->pid = -1;
	node->status = -1;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->shell = sh;
	return (node);
}
