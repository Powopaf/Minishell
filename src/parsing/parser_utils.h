/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:01:36 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/12 16:29:40 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

# include "../../struct.h"

/**
 * Parses redirections for an AST node.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} ast_node - AST node to fill.
 * @param {t_token **} token - Current token pointer.
 * @returns {int} EXIT_SUCCESS or EXIT_FAILURE.
 */
int	parse_redir(t_shell *sh, t_ast *ast_node, t_token **token);

/**
 * Parses command arguments into an AST node.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - AST node to fill.
 * @param {t_token **} tokens - Current token pointer.
 * @returns {int} EXIT_SUCCESS or EXIT_FAILURE.
 */
int	parse_command_args(t_shell *sh, t_ast *node, t_token **tokens);

#endif
