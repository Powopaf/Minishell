/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:20:44 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/24 00:32:42 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	include_wildcard(char *s)
{
	size_t	i;
	size_t	squotes;
	size_t	dquotes;

	i = 0;
	squotes = 0;
	dquotes = 0;
	while (s && s[i])
	{
		if (s[i] == '\'')
			squotes++;
		else if (s[i] == '"')
			dquotes++;
		else if (s[i] == '*' && squotes % 2 == 0 && dquotes % 2 == 0)
			return (1);
		i++;
	}
	return (0);
}

char	lowercase(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ' ');
	return (c);
}

int	strcmp_lowercase(char *s1, char *s2)
{
	while (*s1 && *s2 && lowercase(*s1) == lowercase(*s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)lowercase(*s1) - (unsigned char)lowercase(*s2));
}

void	sort_ascii(char **s)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (!s || !*s)
		return ;
	i = 0;
	j = 1;
	while (s[i])
	{
		while (s[j])
		{
			if (strcmp_lowercase(s[i], s[j]) > 0)
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
			j++;
		}
		i++;
		j = i + 1;
	}
}
