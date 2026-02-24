/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:11:01 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/24 10:30:16 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../error/err.h"
#include "syntax.h"

int	and_syntax(t_shell *sh, t_token *current)
{
	if (current->kw == AND)
	{
		if (!current->prev || current->prev->kw == PIPE
			|| current->prev->kw == L_PARENTH || current->prev->kw == OR
			|| current->prev->kw == AND || current->prev->kw == SEMICOLON)
		{
			syntax_error(sh, AND, -MISUSE);
			return (0);
		}
		if (!current->next || current->next->kw == EOFKW)
			return (syntax_completion(sh));
	}
	return (1);
}

int	or_syntax(t_shell *sh, t_token *current)
{
	if (current->kw == OR)
	{
		if (!current->prev || current->prev->kw == PIPE
			|| current->prev->kw == L_PARENTH || current->prev->kw == OR
			|| current->prev->kw == AND || current->prev->kw == SEMICOLON)
		{
			syntax_error(sh, OR, -MISUSE);
			return (0);
		}
		if (!current->next || current->next->kw == EOFKW)
			return (syntax_completion(sh));
	}
	return (1);
}

int	semicolon_syntax(t_shell *sh, t_token *current)
{
	if (current->kw == SEMICOLON && current->next
		&& current->next->kw == SEMICOLON)
	{
		syntax_error(sh, D_SEMICOLON, -MISUSE);
		return (0);
	}
	if (current->kw == SEMICOLON && (!current->prev || current->prev->kw == PIPE
			|| current->prev->kw == SEMICOLON || current->prev->kw == L_PARENTH
			|| current->prev->kw == OR || current->prev->kw == AND))
	{
		syntax_error(sh, SEMICOLON, -MISUSE);
		return (0);
	}
	return (1);
}

int	ampersand_syntax(t_shell *sh, t_token *current)
{
	if (current->kw == AMPERSAND)
	{
		syntax_error(sh, AMPERSAND, -MISUSE);
		return (0);
	}
	return (1);
}
