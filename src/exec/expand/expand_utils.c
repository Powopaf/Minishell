/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:47:19 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/18 15:27:51 by flomulle         ###   ########.fr       */
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

int	is_quoted(char *s)
{
	size_t	i;
	size_t	squote;
	size_t	dquote;

	squote = 0;
	dquote = 0;
	i = 0;
	if (!s)
		return (0);
	while (i < ft_strlen(s))
	{
		if (s[i] == '\'' && !dquote)
			squote++;
		else if (s[i] == '\"' && !squote)
			dquote++;
		i++;
	}
	return (squote + dquote);
}

char	*strdup_rm_quotes(char *s)
{
	char	*dup;
	size_t	i;
	size_t	j;
	size_t	squote;
	size_t	dquote;

	dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(*dup));
	if (dup == NULL)
		return (NULL);
	squote = 0;
	dquote = 0;
	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == '\'' && !dquote)
			squote = !squote;
		else if (s[i] == '\"' && !squote)
			dquote = !dquote;
		else
			dup[j++] = s[i];
		i++;
	}
	dup[j] = '\0';
	return (dup);
}

int	arr_rm_quotes(char ***arr)
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
		tmp[i] = strdup_rm_quotes((*arr)[i]);
		if (!tmp[i])
			return (ft_free_array_strs(&tmp), 0);
		i++;
	}
	tmp[strslen(*arr)] = NULL;
	ft_empty_array_strs(*arr);
	*arr = tmp;
	return (1);
}
