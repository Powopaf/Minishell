/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_custom_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:09:22 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/19 12:23:06 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "expand_custom_split.h"

void	handle_quotes(char *s, size_t *i)
{
	size_t	squote;
	size_t	dquote;

	squote = 0;
	dquote = 0;
	if (s[*i] == '\'')
		squote++;
	if (s[*i] == '\"')
		dquote++;
	(*i)++;
	while (s[*i] && ((squote && s[*i] != '\'') || (dquote && s[*i] != '\"')))
		(*i)++;
	if (!s[*i])
		(*i)--;
}

static int	ft_count_words(char *s)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
		{
			if (s[i] == '\'' || s[i] == '\"')
				handle_quotes(s, &i);
			i++;
		}
	}
	return (count);
}

static char	*ft_strndup(char *s, size_t n)
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

static size_t	ft_lenbnext(char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (s[n + i] && s[n + i] != ' ' && s[n + i] != '\n' && s[n + i] != '\t')
	{
		if (s[n + i] == '\'' || s[n + i] == '\"')
			handle_quotes(s + n, &i);
		i++;
	}
	return (i);
}

char	**split(char *s)
{
	char	**p;
	size_t	i;
	size_t	w;

	if (!s)
		return (NULL);
	p = (char **)malloc((ft_count_words(s) + 1) * sizeof(*p));
	if (!p)
		return (NULL);
	i = 0;
	w = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (!s[i])
			break ;
		p[w] = ft_strndup((s + i), ft_lenbnext(s, i));
		if (!p[w])
			return (ft_freeall(p, w));
		w++;
		i += ft_lenbnext(s, i);
	}
	p[w] = NULL;
	return (p);
}
