/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_rm_backslash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:47:19 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/23 23:40:15 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static size_t	strslen(char **s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	quote_status(char *s, size_t pos)
{
	size_t	squote;
	size_t	dquote;
	size_t	i;

	i = 0;
	squote = 0;
	dquote = 0;
	while (i < pos)
	{
		if (s[i] == '\'' && !dquote && (!i || s[i - 1] != '\\'))
			squote = !squote;
		if (s[i] == '\"' && !squote && (!i || s[i - 1] != '\\'))
			dquote = !dquote;
		i++;
	}
	if (squote || dquote)
		return (1);
	return (0);
}

static char	*strdup_rm_backslash(char *s)
{
	char	*dup;
	size_t	i;
	size_t	j;

	dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(*dup));
	if (!dup)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == '\\' && (!i || s[i - 1] != '\\') && !quote_status(s, i))
			;
		else
		{
			dup[j++] = s[i];
			if (s[i] == '\\')
				s[i] = ' ';
		}
		i++;
	}
	dup[j] = '\0';
	return (dup);
}

int	arr_rm_backslash(char ***arr)
{
	char	**tmp;
	size_t	i;

	if (!*arr)
		return (1);
	tmp = (char **)malloc((strslen(*arr) + 1) * sizeof(*tmp));
	if (!tmp)
		return (0);
	i = 0;
	while (i < strslen(*arr))
	{
		tmp[i] = strdup_rm_backslash((*arr)[i]);
		if (!tmp[i])
			return (ft_free_array_strs(&tmp), 0);
		i++;
	}
	tmp[strslen(*arr)] = NULL;
	ft_empty_array_strs(*arr);
	*arr = tmp;
	return (1);
}
