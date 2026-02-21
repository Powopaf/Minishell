/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:12:37 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/20 18:37:45 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "err.h"
#include <stdlib.h>
#include <unistd.h>

char	*error_non_tty(t_shell *sh)
{
	char	*s;
	char	*tmp;

	s = ft_strdup("line ");
	tmp = ft_itoa(sh->line_cnt);
	s = ft_strjoin_free(&s, &tmp, 3);
	s = ft_strjoin_char(s, ':', 1, 1);
	s = ft_strjoin_char(s, ' ', 1, 1);
	return (s);
}

char	*join_err(t_shell *sh, char *context, char *why)
{
	char *s;
	char *sb;
	char *tmp;

	if (sh->tty)
		s = ft_strjoin(PROMPT_MES, context);
	else
	{
		s = error_non_tty(sh);
		tmp = ft_strjoin(PROMPT_MES, s);
		if (s)
			free(s);
		s = ft_strjoin(tmp, context);
	}
	s = ft_strjoin_char_p(&s, ':', 1, 1);
	s = ft_strjoin_char_p(&s, ' ', 1, 1);
	sb = ft_strjoin(s, why);
	if (s)
		free(s);
	s = ft_strjoin_char_p(&sb, '\n', 1, 1);
	return (s);
}
