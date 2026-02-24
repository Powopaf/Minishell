/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:05:36 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/24 16:33:09 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "../../error/err.h"
#include "../../../redir.h"
#include <stdlib.h>
#include <unistd.h>
#include "../../../libft/libft.h"

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
	node->parent = NULL;
	node->shell = sh;
	return (node);
}
