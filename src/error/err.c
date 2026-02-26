/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:08:41 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/26 10:01:55 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../1_tokenization/tokens.h"
#include "../clean/clean_shell.h"
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
	s = ft_strjoin(sh->name_err, WARNING);
	if (!s)
		return (error(sh, "malloc", strerror(errno), -FAIL));
	s = ft_strjoin_free(&s, &txt1, 1);
	if (!s)
		return (error(sh, "malloc", strerror(errno), -FAIL));
	line_count = ft_itoa(sh->line_cnt);
	if (!line_count)
		return (free(s), error(sh, "malloc", strerror(errno), -FAIL));
	s = ft_strjoin_free(&s, &line_count, 3);
	if (!s)
		return (error(sh, "malloc", strerror(errno), -FAIL));
	s = ft_strjoin_free(&s, &txt2, 1);
	if (!s)
		return (error(sh, "malloc", strerror(errno), -FAIL));
	write(1, "\n", 1);
	write(2, s, ft_strlen(s));
	free(s);
}

static void	sanitize_copy(char **context, char **tmp, size_t count)
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

static char	*sanitize(char **context)
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
	{
		tmp = ft_strdup(*context);
		return (tmp);
	}
	tmp = malloc(ft_strlen(*context) + count + 3 + 1);
	sanitize_copy(context, &tmp, count);
	return (tmp);
}

void	export_msg(t_shell *sh, char *context)
{
	char	*tmp;
	char	*suffix;

	tmp = ft_strjoin("`", context);
	if (!tmp)
		return (error(sh, "malloc", strerror(errno), EXIT_FAILURE));
	suffix = "': not a valid identifier";
	tmp = ft_strjoin_free(&tmp, &suffix, 1);
	if (!tmp)
		return (error(sh, "malloc", strerror(errno), EXIT_FAILURE));
	error(sh, "export", tmp, EXIT_FAILURE);
	free(tmp);
}

void	error(t_shell *shell, char *context, char *why, int exitno)
{
	char	*s;
	char	*tmp;

	tmp = sanitize(&context);
	s = join_err(shell, tmp, why);
	if (tmp)
		free(tmp);
	if (!s)
		write(2, MALLOC_FULL_ERR, ft_strlen(MALLOC_FULL_ERR));
	else
	{
		write(2, s, ft_strlen(s));
		free(s);
	}
	if (exitno >= 0)
		shell->status = exitno;
	if (exitno < 0)
	{
		shell->status = -exitno;
		return ;
	}
	clean_shell(shell);
	close_std_fds();
	exit(exitno);
}
