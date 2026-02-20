/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:38:02 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/20 09:12:02 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stddef.h>
#include "ast/ast.h"
#include "parser_utils.h"

static t_ast	*parse_pipelines(t_shell *sh, t_token **tokens);

static t_ast	*parse_logical_operators(t_shell *sh, t_token **tokens)
{
	t_ast	*node;
	t_ast	*left;

	node = NULL;
	left = parse_pipelines(sh, tokens);
	if (!left)
		return (NULL);
	while ((*tokens) && ((*tokens)->kw == AND || (*tokens)->kw == OR))
	{
		if ((*tokens)->kw == AND)
			node = create_ast_node(sh, AST_AND);
		else
			node = create_ast_node(sh, AST_OR);
		if (!node)
			return (NULL);
		node->left = left;
		(*tokens) = (*tokens)->next;
		node->right = parse_pipelines(sh, tokens);
		if (!node->right)
			return (NULL);
		left = node;
	}
	return (left);
}

static t_ast	*parse_subshell(t_shell *sh, t_token **tokens)
{
	t_ast	*node;

	(*tokens) = (*tokens)->next;
	node = create_ast_node(sh, AST_SUBSHELL);
	if (!node)
		return (NULL);
	node->left = parse_logical_operators(sh, tokens);
	if (!node->left)
		return (NULL);
	if (!*tokens || (*tokens)->kw != R_PARENTH)
		return (NULL);
	(*tokens) = (*tokens)->next;
	if (parse_redir(sh, node, tokens))
		return (NULL);
	return (node);
}

static t_ast	*parse_command(t_shell *sh, t_token **tokens)
{
	t_ast	*node;

	if ((*tokens) && (*tokens)->kw == L_PARENTH)
	{
		node = parse_subshell(sh, tokens);
		if (!node)
			return (NULL);
		return (node);
	}
	node = create_ast_node(sh, AST_CMD);
	if (!node)
		return (NULL);
	while ((*tokens) && ((*tokens)->kw == WORD || (*tokens)->kw == REDIR_IN
		|| (*tokens)->kw == REDIR_HD || (*tokens)->kw == REDIR_OUT
		|| (*tokens)->kw == REDIR_APP))
	{
		if (parse_redir(sh, node, tokens))
			return (NULL);
		if (parse_command_args(sh, node, tokens))
			return (NULL);
	}
	return (node);
}

static t_ast	*parse_pipelines(t_shell *sh, t_token **tokens)
{
	t_ast	*node;
	t_ast	*left;

	left = parse_command(sh, tokens);
	if (!left)
		return (NULL);
	node = NULL;
	while (*tokens && (*tokens)->kw == PIPE)
	{
		node = create_ast_node(sh, AST_PIPE);
		if (!node)
			return (NULL);
		node->left = left;
		(*tokens) = (*tokens)->next;
		node->right = parse_command(sh, tokens);
		if (!node->right)
			return (NULL);
		left = node;
	}
	return (left);
}

t_ast	*parser(t_shell *sh, t_token **tokens)
{
	t_ast	*node;

	node = parse_logical_operators(sh, tokens);
	if (!node || (tokens && (*tokens)->kw != EOFKW))
		return (NULL);
	return (node);
}
