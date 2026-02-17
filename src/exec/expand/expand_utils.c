/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:47:19 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/17 09:53:25 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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

// static char	*copy_rm_quotes(char *s, char *dup)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	squote;
// 	size_t	dquote;
// 	char	*clean;

// 	squote = 0;
// 	dquote = 0;
// 	i = 0;
// 	j = 0;
// 	while (i < ft_strlen(s))
// 	{
// 		if (s[i] == '\'' && !dquote)
// 			squote = !squote;
// 		else if (s[i] == '\"' && !squote)
// 			dquote = !dquote;
// 		else
// 			dup[j++] = s[i];
// 		i++;
// 	}
// 	dup[j] = '\0';
// 	clean = ft_strdup(dup);
// 	free(dup);
// 	return (clean);
// }

// char	*strdup_rm_quotes(char *s)
// {
// 	char	*dup;

// 	dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(*dup));
// 	if (dup == NULL)
// 		return (NULL);
// 	dup = copy_rm_quotes(s, dup);
// 	return (dup);
// }

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
	ft_empty_array_strs(*arr);
	*arr = tmp;
	return (1);
}

// static char	**addstr_rm_quote(char **arr, char *s)
// {
// 	char	**tmp;
// 	size_t	i;

// 	tmp = (char **)malloc((strslen(arr) + 2) * sizeof(*tmp));
// 	if (!tmp)
// 		return (NULL);
// 	i = 0;
// 	while (arr && arr[i])
// 	{
// 		tmp[i] = ft_strdup(arr[i]);
// 		if (!tmp[i++])
// 			return (ft_free_array_strs(&tmp), NULL);
// 	}
// 	if (s)
// 		tmp[i] = ft_strdup(s);
// 	else
// 		tmp[i] = ft_strdup("");
// 	if (!tmp[i])
// 		return (ft_free_array_strs(&tmp), NULL);
// 	tmp[i + 1] = NULL;
// 	return (tmp);
// }

// int	addstr_arr_rm_quotes(char ***arr, char *s)
// {
// 	char	**tmp;

// 	if (!*arr)
// 	{
// 		tmp = malloc(2 * sizeof(char *));
// 		if (!tmp)
// 			return (0);
// 		tmp[0] = ft_strdup(s);
// 		if (!tmp[0])
// 			return (free(tmp), 0);
// 		tmp[1] = NULL;
// 		if (arr && *arr)
// 			ft_empty_array_strs(*arr);
// 		*arr = tmp;
// 		return (1);
// 	}
// 	tmp = addstr_rm_quote(*arr, s);
// 	if (!tmp)
// 		return (0);
// 	ft_empty_array_strs(*arr);
// 	*arr = tmp;
// 	return (1);
// }
