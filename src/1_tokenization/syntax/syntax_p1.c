/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_p1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:18:16 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/24 08:18:24 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../error/err.h"
#include "syntax.h"

static int	redir_syntax(t_shell *sh, t_token *current)
{
	if (current->kw == REDIR_IN || current->kw == REDIR_HD
		|| current->kw == REDIR_OUT || current->kw == REDIR_APP)
	{
		if (current->next && current->next->kw != WORD)
		{
			syntax_error(sh, current->next->kw, -MISUSE);
			return (0);
		}
	}
	return (1);
}

static int	pipe_syntax(t_shell *sh, t_token *current)
{
	if (current->kw == PIPE)
	{
		if (!current->prev || current->prev->kw == PIPE
			|| current->prev->kw == L_PARENTH || current->prev->kw == AND
			|| current->prev->kw == OR || current->prev->kw == SEMICOLON)
		{
			syntax_error(sh, PIPE, -MISUSE);
			return (0);
		}
		if (!current->next || current->next->kw == EOFKW)
			return (syntax_completion(sh));
	}
	return (1);
}

static int	parenth_syntax(t_shell *sh)
{
	t_token	*current;
	int		count;

	current = sh->tokens;
	count = 0;
	while (current)
	{
		if (current->kw == L_PARENTH)
		{
			count++;
			if (current->next && current->next->kw == R_PARENTH)
				return (syntax_error(sh, R_PARENTH, -MISUSE), 0);
			if (current->prev && current->prev->kw == WORD
				&& (!current->prev->prev || !is_redir(current->prev->prev)))
				return (syntax_error(sh, L_PARENTH, -MISUSE), 0);
		}
		else if (current->kw == R_PARENTH)
			count--;
		if (count < 0)
			return (syntax_error(sh, R_PARENTH, -MISUSE), 0);
		current = current->next;
	}
	if (count > 0)
		return (syntax_completion(sh));
	return (1);
}

int	check_syntax(t_shell *sh)
{
	t_token	*current;

	if (!sh->tokens)
		return (0);
	if (!parenth_syntax(sh))
		return (0);
	current = sh->tokens;
	while (current)
	{
		if (!redir_syntax(sh, current))
			return (0);
		if (!or_syntax(sh, current))
			return (0);
		if (!pipe_syntax(sh, current))
			return (0);
		if (!and_syntax(sh, current))
			return (0);
		if (!semicolon_syntax(sh, current))
			return (0);
		if (!ampersand_syntax(sh, current))
			return (0);
		current = current->next;
	}
	return (1);
}
