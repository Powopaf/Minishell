/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:01:36 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/05 23:01:40 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

#include "../../struct.h"

int	parse_redir(t_shell *sh, t_ast *ast_node, t_token **token);
int	parse_command_args(t_shell *sh, t_ast *node, t_token **tokens);

#endif
