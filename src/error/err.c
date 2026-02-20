/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:08:41 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/20 17:05:11 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../clean/clean_shell.h"
#include "../parsing/token/tokens.h"
#include "err.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void	warning_hd(t_shell *sh)
{
	char	*s;
	char	*txt1;
	char	*txt2;
	char	*line_count;

	txt1 = "here-document at line ";
	txt2 = " delimited by end-of-file (wanted `eof')\n";
	s = ft_strjoin(PROMPT_MES, WARNING);
	if (!s)
		return (error(sh, "malloc", MALLOC_ERR, -FAIL));
	s = ft_strjoin_free(&s, &txt1, 1);
	if (!s)
		return (error(sh, "malloc", MALLOC_ERR, -FAIL));
	line_count = ft_itoa(sh->line_cnt);
	if (!line_count)
		return (free(s), error(sh, "malloc", MALLOC_ERR, -FAIL));
	s = ft_strjoin_free(&s, &line_count, 3);
	if (!s)
		return (error(sh, "malloc", MALLOC_ERR, -FAIL));
	s = ft_strjoin_free(&s, &txt2, 1);
	if (!s)
		return (error(sh, "malloc", MALLOC_ERR, -FAIL));
	write(1, "\n", 1);
	write(2, s, ft_strlen(s));
	free(s);
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

void	sanitize_copy(char **context, char **tmp, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	(*tmp)[0] = '$';
	(*tmp)[1] = '\'';
	j = 2;
	while ((*context)[i])
	{
		if ((*context)[i] == '\n')
		{
			(*tmp)[i + j] = '\\';
			(*tmp)[i + (++j)] = 'n';
		}
		else
			(*tmp)[i + j] = (*context)[i];
		i++;
	}
	(*tmp)[i + count + 2] = '\'';
	(*tmp)[i + count + 3] = '\0';
}

char *sanitize(char **context)
{
	char	*tmp;
	size_t	i;
	size_t	count;

	count = 0;
	i = -1;
	while ((*context)[++i])
		if ((*context)[i] == '\n')
			count++;
	if (!count)
		return (NULL);
	tmp = malloc(ft_strlen(*context) + count + 3 + 1);
	if (!tmp)
		return (NULL);
	sanitize_copy(context, &tmp, count);
	return (tmp);
}

void	error(t_shell *shell, char *context, char *why, int exitno)
{
	char	*s;
	char	*tmp;

	tmp = sanitize(&context);
	s = join_err(tmp, why);
	if (tmp)
		free(tmp);
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
