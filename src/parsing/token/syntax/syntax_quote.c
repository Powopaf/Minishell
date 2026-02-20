/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:14:12 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/20 16:52:38 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../error/err.h"
#include "../../../../libft/libft.h"
#include "../../../signal/signal_handling.h"
#include "../../../exec/heredocs/heredoc.h"
#include "syntax.h"

int	complete_line(t_shell *sh, char c)
{
	char	*line;

	setup_heredoc_signals();
	sh->line = ft_strjoin_char(sh->line, '\n', 1, 1);
	while (1)
	{
		ft_putstr_fd(PROMPT_HD, 1);
		line = ft_get_next_line(sh->stdin_fd);
		if (!line)
		{
			quote_error(sh, &c);
			return (0);
		}
		sh->line = ft_strjoin_free(&sh->line, &line, 1);
		if (ft_strchr(line, c))
		{
			sh->line[ft_strlen(sh->line) - 1] = 0;
			free(line);
			return (setup_signals(sh), 1);
		}
	}
}

int	missing_quote(t_shell *sh, size_t squote, size_t dquote)
{
	char c;
	if (!sh->tty)
	{
		if (squote)
			quote_error(sh, "\'");
		if (dquote)
			quote_error(sh, "\"");
		return (0);
	}
	if (squote)
		c = '\'';
	else if (dquote)
		c = '\"';
	else
		return (0);
	return (complete_line(sh, c));
}

int	search_next_quote(t_shell *sh, size_t *squote, size_t *dquote, size_t *i)
{
	if (*squote)
	{
		while (sh->line[*i] != '\'' && sh->line[*i - 1] != '\\')
		{
			if (!sh->line[*i] || !sh->line[*i + 1])
				return (missing_quote(sh, *squote, *dquote));
			(*i)++;
		}
		*squote = !(*squote);
		return (1);
	}
	if (*dquote)
	{
		while (sh->line[*i] != '\"' && sh->line[*i - 1] != '\\')
		{
			if (!sh->line[*i] || !sh->line[*i + 1])
				return (missing_quote(sh, *squote, *dquote));
			(*i)++;
		}
		*dquote = !(*dquote);
		return (1);
	}
	return (1);
}

int	quote_syntax(t_shell *sh)
{
	size_t	i;
	size_t	squote;
	size_t	dquote;

	squote = 0;
	dquote = 0;
	i = -1;
	while (sh->line && sh->line[++i])
	{
		if (sh->line[i] == '\'' && (!i || sh->line[i - 1] != '\\') && !dquote)
		{
			squote = !squote;
			i++;
			if (squote && !search_next_quote(sh, &squote, &dquote, &i))
				return (0);
		}
		if (sh->line[i] == '\"' && (!i || sh->line[i - 1] != '\\') && !squote)
		{
			dquote = !dquote;
			i++;
			if (dquote && !search_next_quote(sh, &squote, &dquote, &i))
				return (0);
		}
	}
	return (1);
}
