/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:56:32 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/03 11:05:45 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/1_tokenization/1_1_tokens/token_utils.h"
#include "./src/1_tokenization/1_1_tokens/tokens.h"
#include "./src/1_tokenization/1_2_syntax/syntax.h"
#include "./src/3_execution/3_1_expansion/expand.h"
#include "./src/7_error_handling/err.h"
#include <stdlib.h>

static void	handle_quotes(char *s, ssize_t *i)
{
	size_t	squotes;
	size_t	dquotes;

	squotes = 0;
	dquotes = 0;
	if (s[*i] == '\'' && !is_backslashed(s, *i))
		squotes = !squotes;
	else if (s[*i] == '\"' && !is_backslashed(s, *i))
		dquotes = !dquotes;
	(*i)++;
	while (s[*i] && (squotes % 2 == 1 || dquotes % 2 == 1))
	{
		if (s[*i] == '\'' && !is_backslashed(s, *i) && !dquotes)
			squotes = !squotes;
		else if (s[*i] == '\"' && !is_backslashed(s, *i) && !squotes)
			dquotes = !dquotes;
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
	while (sh->line[i] && (!isshspace(sh->line[i]) || (isshspace(sh->line[i])
				&& is_backslashed(sh->line, i))) && !isshellkw(sh->line[i])
		&& !isshbreak(sh->line[i]))
	{
		if ((sh->line[i] == '\'' && !is_backslashed(sh->line, i))
			|| (sh->line[i] == '\"' && !is_backslashed(sh->line, i)))
			handle_quotes(sh->line, &i);
		i++;
	}
	if (i > beginning)
	{
		word = ft_substr(sh->line, beginning, i - beginning);
		if (!word)
			return (error(sh, "malloc", strerror(errno), -FAIL), i);
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
		while ((isshspace(sh->line[i]) && !is_backslashed(sh->line, i))
			|| isshbreak(sh->line[i]))
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
