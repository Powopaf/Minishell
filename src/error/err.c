/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:08:41 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/06 15:58:17 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../parsing/token/tokens.h"
#include "../clean/clean_shell.h"
#include "../../libft/libft.h"

void	syntax_error(t_shell *sh, t_token_kw kw, int exitno)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(ft_token_to_char(kw), 2);
	ft_putendl_fd("'", 2);
	sh->status = -exitno;
	if (exitno >= 0)
	{
		clean_shell(sh);
		exit(exitno);
	}
}

static char	*join_err(char *context, char *why)
{
	char	*s;
	char	*sb;

	s = ft_strjoin(PROMPT_MES, context);
	s = ft_strjoin_char_p(&s, ':', 1, 1);
	s = ft_strjoin_char_p(&s, ' ', 1, 1);
	sb = ft_strjoin(s, why);
	if (s)
		free(s);
	s = ft_strjoin_char_p(&sb, '\n', 1, 1);
	return (s);
}

void	error(t_shell *shell, char *context, char *why, int exitno)
{
	char	*s;

	s = join_err(context, why);
	if (!s)
		write(2, MALLOC_FULL_ERR, ft_strlen(MALLOC_FULL_ERR));
	else
	{
		write(2, s, ft_strlen(s));
		free(s);
	}
	if (!exitno && errno == EACCES)
		exitno = CMD_PERM_DND;
	else if (!exitno && errno == ENOENT)
		exitno = CMD_NOT_FND;
	else if (!exitno)
		exitno = EXIT_FAILURE;
	shell->status = -exitno;
	if (exitno < 0)
		return ;
	clean_shell(shell);
	exit(exitno);
}
