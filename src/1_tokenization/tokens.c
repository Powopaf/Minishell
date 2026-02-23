/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:56:32 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/23 22:47:57 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../error/err.h"
#include "syntax/syntax.h"
#include "token_utils.h"
#include "tokens.h"
#include <stdlib.h>

static void	handle_quotes(char *s, ssize_t *i)
{
	size_t	squotes;
	size_t	dquotes;

	squotes = 0;
	dquotes = 0;
	if (s[*i] == '\'')
		squotes++;
	if (s[*i] == '\"')
		dquotes++;
	(*i)++;
	while (s[*i] && (squotes % 2 == 1 || dquotes % 2 == 1))
	{
		if (s[*i] == '\'')
			squotes++;
		if (s[*i] == '\"')
			dquotes++;
		if ((squotes % 2 == 0 && dquotes % 2 == 0))
			break ;
		(*i)++;
	}
	if (!s[*i])
		(*i)--;
}

static ssize_t	add_word_token(t_shell *sh, ssize_t i)
{
	ssize_t	beginning;
	char	*word;

	beginning = i;
	while (sh->line[i]
		&& !(isshspace(sh->line[i]) && (!i || sh->line[i - 1] != '\\'))
		&& !isshellkw(sh->line[i])
		&& !isshbreak(sh->line[i]))
	{
		if (sh->line[i] == '\'' || sh->line[i] == '\"')
			handle_quotes(sh->line, &i);
		i++;
	}
	if (i > beginning)
	{
		word = ft_substr(sh->line, beginning, i - beginning);
		if (!word)
			return (error(sh, "malloc", MALLOC_ERR, -FAIL), i);
		add_token(sh, word, WORD);
		free(word);
	}
	return (i);
}

int	tokenization(t_shell *sh)
{
	ssize_t	i;

	if (!backslash_syntax(sh))
		return (0);
	if (!quote_syntax(sh))
		return (0);
	i = 0;
	while (sh->line[i])
	{
		while (isshspace(sh->line[i]) && (!i || sh->line[i - 1] != '\\'))
			i++;
		if (!sh->line[i])
			break ;
		if (isshellkw(sh->line[i]))
			i = add_key_token(sh, i);
		else
			i = add_word_token(sh, i);
		if (i == -1)
			return (0);
	}
	add_token(sh, NULL, EOFKW);
	return (1);
}
