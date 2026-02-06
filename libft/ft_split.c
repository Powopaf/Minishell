/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:06:40 by flomulle          #+#    #+#             */
/*   Updated: 2025/12/11 13:26:04 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	size_t	i;
	char	*dup;

	if (s == NULL)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	if (n > len)
		n = len;
	dup = (char *)malloc((n + 1) * sizeof(*dup));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[n] = '\0';
	return (dup);
}

static char	**ft_freeall(char **p, size_t w)
{
	size_t	i;

	i = 0;
	while (i < w)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

size_t	ft_lenbnext(const char *s, size_t n, char c)
{
	size_t	i;

	i = 0;
	while (s[n + i] && s[n + i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	size_t	i;
	size_t	w;

	if (!s)
		return (NULL);
	p = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(*p));
	if (!p)
		return (NULL);
	i = 0;
	w = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		p[w] = ft_strndup((s + i), ft_lenbnext(s, i, c));
		if (!p[w])
			return (ft_freeall(p, w));
		w++;
		i += ft_lenbnext(s, i, c);
	}
	p[w] = NULL;
	return (p);
}
