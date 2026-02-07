/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:58:42 by flomulle          #+#    #+#             */
/*   Updated: 2025/12/10 22:37:53 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

size_t	strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*strchr_gnl(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*strjoin_gnl(char *s1, char *s2)
{
	char	*res;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	res = malloc(sizeof(char) * (strlen_gnl(s1) + strlen_gnl(s2) + 1));
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	cpy_gnl(res, s1, s2);
	free(s1);
	return (res);
}

void	cpy_gnl(char *res, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	if (!res || !s1 || !s2)
		return ;
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
}
