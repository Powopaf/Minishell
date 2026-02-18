/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:36:37 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/18 10:47:37 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_strslen(char **s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	**ft_single_str_array(char *s)
{
	char	**tmp;

	if (!s || !*s)
		return (NULL);
	tmp = (char **)malloc(2 * sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp[0] = ft_strdup(s);
	if (!tmp[0])
	{
		free(tmp);
		return (NULL);
	}
	tmp[1] = NULL;
	return (tmp);
}

static char	**ft_util(char **arr, char *s)
{
	char	**tmp;
	size_t	i;

	tmp = (char **)malloc((ft_strslen(arr) + 2) * sizeof(*tmp));
	if (!tmp)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		tmp[i] = ft_strdup(arr[i]);
		if (!tmp[i++])
		{
			ft_free_array_strs(&tmp);
			return (NULL);
		}
	}
	tmp[i] = ft_strdup(s);
	if (!tmp[i])
	{
		ft_free_array_strs(&tmp);
		return (NULL);
	}
	tmp[i + 1] = NULL;
	return (tmp);
}

char	**ft_add_str_array(char **arr, char *s)
{
	char	**tmp;

	if (!arr || !*arr)
	{
		tmp = ft_single_str_array(s);
		return (tmp);
	}
	if (!s || !*s)
	{
		tmp = ft_strsdup(arr);
		return (tmp);
	}
	tmp = ft_util(arr, s);
	ft_empty_array_strs(arr);
	return (tmp);
}
