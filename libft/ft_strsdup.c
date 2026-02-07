/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:11:18 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/14 17:52:04 by flomulle         ###   ########.fr       */
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

char	**ft_strsdup(char **s)
{
	size_t	i;
	char	**dup;

	if (!s)
		return (NULL);
	dup = (char **)malloc((ft_strslen(s) + 1) * sizeof(*dup));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = ft_strdup(s[i]);
		if (!dup[i])
		{
			ft_free_array_strs(&dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
