/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_complete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:08:24 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/23 20:12:12 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../../clean/clean_shell.h"
#include "../../error/err.h"
#include "../../exec/heredocs/heredoc.h"
#include "../../signal/signal_handling.h"
#include "../tokens.h"
#include "syntax.h"

size_t	count_backslash(t_shell *sh)
{
	int		i;
	size_t	count;

	if (!ft_strlen(sh->line))
		return (0);
	i = ft_strlen(sh->line) - 1;
	count = 0;
	while (i >= 0 && sh->line[i] == '\\')
	{
		count++;
		i--;
	}
	return (count);
}

int	backslash_syntax(t_shell *sh)
{
	char	*add;

	if (count_backslash(sh) % 2 == 0)
		return (1);
	setup_heredoc_signals();
	while (count_backslash(sh) % 2 == 1)
	{
		sh->line[ft_strlen(sh->line) - 1] = '\0';
		add = readline("> ");
		if (!add)
			break ;
		sh->line = ft_strjoin_free(&sh->line, &add, 1);
		free(add);
		if (!sh->line)
			return (error(sh, "malloc", strerror(errno), -1), 0);
	}
	setup_signals(sh);
	return (1);
}

static int	complete_syntax(t_shell *sh)
{
	char	*add;

	add = readline("> ");
	sh->line = ft_strjoin_free(&sh->line, &add, 3);
	if (!sh->line)
		return (0);
	return (1);
}

int	syntax_completion(t_shell *sh)
{
	if (!complete_syntax(sh))
		return (0);
	tokens_clear(&sh->tokens, clean_token);
	if (!tokenization(sh))
		return (0);
	return (check_syntax(sh));
}
