/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:36:37 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/20 11:02:05 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		if (!s || !*s)
			return (NULL);
		tmp = ft_strsdup(&s);
		return (tmp);
	}
	if (!s || !*s)
	{
		tmp = ft_strsdup(arr);
		return (tmp);
	}
	tmp = ft_util(arr, s);
	ft_empty_array_strs(arr);
	free(arr);
	return (tmp);
}
