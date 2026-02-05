/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_adding.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:03:51 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/19 17:49:55 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_utils.h"
#include "../../error/err.h"

static ssize_t	ft_add_key_tokenquad(t_shell *sh, ssize_t i)
{
	if (sh->line[i] == '&' && sh->line[i + 1] != '&')
	{
		syntax_error(sh, AMPERSAND, -MISUSE);
		return (-1);
	}
	if (sh->line[i] == ';')
	{
		syntax_error(sh, SEMICOLON, -MISUSE);
		return (-1);
	}
	error(sh, "token", DEBUG, PRG_ERR);
	return (-1);
}

static ssize_t	ft_add_key_tokenter(t_shell *sh, ssize_t i)
{
	if (sh->line[i] == '|')
	{
		if (add_token(sh, "|", PIPE))
			return (-1);
		return (++i);
	}
	if (sh->line[i] == '(')
	{
		if (add_token(sh, "(", L_PARENTH))
			return (-1);
		return (++i);
	}
	if (sh->line[i] == ')')
	{
		if (add_token(sh, ")", R_PARENTH))
			return (-1);
		return (++i);
	}
	i = ft_add_key_tokenquad(sh, i);
	return (i);
}

static ssize_t	ft_add_key_tokenbis(t_shell *sh, ssize_t i)
{
	if (sh->line[i] == '>' && sh->line[i + 1] == '>')
	{
		if (add_token(sh, ">>", REDIR_APP))
			return (-1);
		i += 2;
		return (i);
	}
	if (sh->line[i] == '<')
	{
		if (add_token(sh, "<", REDIR_IN))
			return (-1);
		return (++i);
	}
	if (sh->line[i] == '>')
	{
		if (add_token(sh, ">", REDIR_OUT))
			return (-1);
		return (++i);
	}
	i = ft_add_key_tokenter(sh, i);
	return (i);
}

ssize_t	add_key_token(t_shell *sh, ssize_t i)
{
	if (sh->line[i] == '|' && sh->line[i + 1] == '|')
	{
		if (!add_token(sh, "||", OR))
			return (-1);
		i += 2;
		return (i);
	}
	if (sh->line[i] == '&' && sh->line[i + 1] == '&')
	{
		if (add_token(sh, "&&", AND))
			return (-1);
		i += 2;
		return (i);
	}
	if (sh->line[i] == '<' && sh->line[i + 1] == '<')
	{
		if (add_token(sh, "<<", REDIR_HD))
			return (-1);
		i += 2;
		return (i);
	}
	i = ft_add_key_tokenbis(sh, i);
	return (i);
}
