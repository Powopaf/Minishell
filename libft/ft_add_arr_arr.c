/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_arr_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:20:39 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/15 18:31:58 by flomulle         ###   ########.fr       */
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

static void	copy_array(char **dest, char **src, int start, int len)
{
	int	i;

	i = 0;
	while (src && i < len)
	{
		dest[start + i] = ft_strdup(src[i]);
		i++;
	}
}

void	ft_add_arr_arr(char ***dest, char **src)
{
	char	**new_arr;

	new_arr = (char **)malloc(sizeof(char *) * ((ft_strslen(*dest)
		+ ft_strslen(src) + 1)));
	if (new_arr == NULL)
		return ;
	copy_array(new_arr, *dest, 0, ft_strslen(*dest));
	copy_array(new_arr, src, ft_strslen(*dest), ft_strslen(src));
	new_arr[ft_strslen(*dest) + ft_strslen(src)] = NULL;
	if (*dest != NULL)
		ft_empty_array_strs(*dest);
	if (src != NULL)
		ft_empty_array_strs(src);
	*dest = new_arr;
}
