/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_complete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:08:24 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/02 01:00:29 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/1_tokenization/1_1_tokens/tokens.h"
#include "./src/1_tokenization/1_2_syntax/syntax.h"
#include "./src/2_parsing_ast/heredoc.h"
#include "./src/5_signal_handling/signal_handling.h"
#include "./src/6_cleaning/clean_shell.h"
#include "./src/7_error_handling/err.h"

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
