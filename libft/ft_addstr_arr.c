/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:23:40 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/26 12:51:13 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**ft_util(char **arr, char *s)
{
	char	**tmp;
	size_t	i;

	tmp = (char **)malloc((ft_strslen(arr) + 2) * sizeof(*tmp));
	if (!tmp)
		return (NULL);
	i = 0;
	while (arr && arr[i])
	{
		tmp[i] = ft_strdup(arr[i]);
		if (!tmp[i++])
			return (ft_free_array_strs(&tmp), NULL);
	}
	if (s)
		tmp[i] = ft_strdup(s);
	else
		tmp[i] = ft_strdup("");
	if (!tmp[i])
		return (ft_free_array_strs(&tmp), NULL);
	tmp[i + 1] = NULL;
	return (tmp);
}

int	ft_addstr_arr(char ***arr, char *s)
{
	char	**tmp;

	if (!*arr)
	{
		tmp = malloc(2 * sizeof(char *));
		if (!tmp)
			return (0);
		tmp[0] = ft_strdup(s);
		if (!tmp[0])
			return (free(tmp), 0);
		tmp[1] = NULL;
		if (arr && *arr)
			ft_empty_array_strs(*arr);
		*arr = tmp;
		return (1);
	}
	tmp = ft_util(*arr, s);
	if (!tmp)
		return (0);
	ft_empty_array_strs(*arr);
	*arr = tmp;
	return (1);
}
