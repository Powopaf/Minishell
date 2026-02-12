/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:56:32 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/12 16:32:56 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "token_utils.h"
#include "../../error/err.h"
#include "../../../libft/libft.h"
#include <stdlib.h>

static ssize_t	add_word_token(t_shell *sh, ssize_t i)
{
	ssize_t	beginning;
	char	*word;

	beginning = i;
	while (sh->line[i] && !isshspace(sh->line[i]) && !isshellkw(sh->line[i])
		&& !isshbreak(sh->line[i]))
	{
		i++;
	}
	if (i > beginning)
	{
		word = ft_substr(sh->line, beginning, i - beginning);
		if (!word)
			error(sh, "malloc", MALLOC_ERR, -FAIL);
		add_token(sh, word, WORD);
		if (word)
			free(word);
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
