/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:56:32 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/19 17:49:33 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "token_utils.h"
#include "../../error/err.h"
#include <stddef.h>

// ssize_t	ft_quotes(t_shell *sh, ssize_t i)
// {
// 	return i;
// }

static ssize_t	add_word_token(t_shell *sh, ssize_t i)
{
	ssize_t	beginning;
	char	*word;

	beginning = i;
	while (sh->line[i] && !isshspace(sh->line[i]) && !isshellkw(sh->line[i])
		&& !isshbreak(sh->line[i]))
	{
		// if (sh->line[i] == '\'' || sh->line[i] == '"')
		// 	i = ft_quotes(sh, i);
		// if (i == -1)
		// 	return (i);
		// else
			i++;
	}
	if (i > beginning)
	{
		word = ft_substr(sh->line, beginning, i - beginning);
		if (!word)
			error(sh, "malloc", MALLOC_ERR, -FAIL);
		add_token(sh, word, WORD);
		ft_free_str(&word);
	}
	return (i);
}

int	tokenization(t_shell *sh)
{
	ssize_t	i;

	i = 0;
	while (sh->line[i])
	{
		while (isshspace(sh->line[i]))
			i++;
		if (!sh->line[i] || isshbreak(sh->line[i]))
			break ;
		if (isshellkw(sh->line[i]))
			i = add_key_token(sh, i);
		else
			i = add_word_token(sh, i);
		if (i == -1)
			return (EXIT_FAILURE);
	}
	add_token(sh, NULL, EOFKW);
	return (EXIT_SUCCESS);
}
// consider cases:
// \ is it for ignoring \n for long script ?
// \n in a script, handle command then start new one ?
