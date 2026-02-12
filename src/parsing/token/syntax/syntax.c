/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:18:16 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/12 16:34:02 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"
#include "../../../error/err.h"

static int	redir_syntax(t_shell *sh)
{
	t_token	*current;

	current = sh->tokens;
	while (current->next)
	{
		if (current->kw == REDIR_IN || current->kw == REDIR_HD
			|| current->kw == REDIR_OUT || current->kw == REDIR_APP)
		{
			if (!current->next || (current->next && current->next->kw != WORD))
			{
				syntax_error(sh, current->next->kw, -MISUSE);
				return (EXIT_FAILURE);
			}
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static int	pipe_syntax(t_shell *sh)
{
	t_token	*current;

	current = sh->tokens;
	while (current->next)
	{
		if (current->kw == PIPE)
		{
			if (!current->prev)
			{
				syntax_error(sh, PIPE, -MISUSE);
				return (EXIT_FAILURE);
			}
			if (current->next && current->next->kw == PIPE)
			{
				syntax_error(sh, PIPE, -MISUSE);
				return (EXIT_FAILURE);
			}
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
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
			count++;
		else if (current->kw == R_PARENTH)
			count--;
		current = current->next;
	}
	if (count > 0)
		syntax_error(sh, L_PARENTH, -MISUSE);
	else if (count < 0)
		syntax_error(sh, R_PARENTH, -MISUSE);
	if (count != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_syntax(t_shell *sh)
{
	if (!sh->tokens)
		return (EXIT_FAILURE);
	if (redir_syntax(sh))
		return (EXIT_FAILURE);
	if (pipe_syntax(sh))
		return (EXIT_FAILURE);
	if (parenth_syntax(sh))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
