/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:26:09 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/27 11:27:17 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../1_tokenization/tokens.h"
#include "../clean/clean_shell.h"
#include "err.h"
#include <stdlib.h>
#include <unistd.h>

static void	syntax_err_non_tty_add_line(t_shell *sh)
{
	char	*s;

	ft_putstr_fd("line ", 2);
	s = ft_itoa(sh->line_cnt);
	if (s)
	{
		ft_putstr_fd(s, 2);
		free(s);
	}
	ft_putstr_fd(": ", 2);
}

static void	syntax_err_non_tty_full_line(t_shell *sh)
{
	syntax_err_non_tty_add_line(sh);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(sh->line, 2);
	ft_putendl_fd("'", 2);
}

void	syntax_error_word(t_shell *sh, char *word, int exitno)
{
	ft_putstr_fd(sh->name_err, 2);
	if (!sh->tty)
		syntax_err_non_tty_add_line(sh);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(word, 2);
	ft_putendl_fd("'", 2);
	if (!sh->tty)
		syntax_err_non_tty_full_line(sh);
	sh->status = -exitno;
	if (exitno >= 0)
	{
		clean_shell(sh);
		exit(exitno);
	}
}

void	syntax_error(t_shell *sh, t_token_kw kw, int exitno)
{
	ft_putstr_fd(sh->name_err, 2);
	if (!sh->tty)
		syntax_err_non_tty_add_line(sh);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(ft_token_to_char(kw), 2);
	ft_putendl_fd("'", 2);
	if (!sh->tty)
		syntax_err_non_tty_full_line(sh);
	sh->status = -exitno;
	if (exitno >= 0)
	{
		clean_shell(sh);
		exit(exitno);
	}
}

void	quote_error(t_shell *sh, char *c)
{
	char	*s;

	ft_putstr_fd(sh->name_err, 2);
	if (!sh->tty)
	{
		ft_putstr_fd("line ", 2);
		s = ft_itoa(sh->line_cnt);
		if (s)
		{
			ft_putstr_fd(s, 2);
			free(s);
		}
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd("unexpected EOF while looking for matching `", 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd("\'\n", 2);
	sh->status = MISUSE;
}
