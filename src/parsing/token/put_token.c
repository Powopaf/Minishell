/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:02:23 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/19 17:05:23 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	*ft_token_to_char(t_token_kw kw)
{
	if (kw == EOFKW)
		return ("newline");
	if (kw == REDIR_IN)
		return ("<");
	if (kw == REDIR_HD)
		return ("<<");
	if (kw == REDIR_OUT)
		return (">");
	if (kw == REDIR_APP)
		return (">>");
	if (kw == L_PARENTH)
		return ("(");
	if (kw == R_PARENTH)
		return (")");
	if (kw == SEMICOLON)
		return (";");
	if (kw == AMPERSAND)
		return ("&");
	if (kw == PIPE)
		return ("|");
	if (kw == AND)
		return ("&&");
	if (kw == OR)
		return ("||");
	return ("Word");
}

char	*ft_astkw_to_char(t_ast_node_type kw)
{
	if (kw == AST_CMD)
		return ("CMD");
	if (kw == AST_PIPE)
		return ("PIPE");
	if (kw == AST_AND)
		return ("&&");
	if (kw == AST_OR)
		return ("||");
	if (kw == AST_SUBSHELL)
		return ("SUBSHELL");
	return ("Error in AST");
}


