/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:08:24 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/20 17:27:19 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include "../../../error/err.h"
#include "../../../exec/heredocs/heredoc.h"
#include "../../../signal/signal_handling.h"
#include "syntax.h"

int	backslash_syntax(t_shell *sh)
{
	char	*add;

	if (sh->line[ft_strlen(sh->line) - 1] == '\\')
	{
		while (sh->line[ft_strlen(sh->line) - 1] == '\\')
		{
			sh->line[ft_strlen(sh->line) - 1] = '\0';
			add = readline("> ");
			sh->line = ft_strjoin_free(&sh->line, &add, 3);
			if (!sh->line)
				return (0);
		}
	}
	return (1);
}
