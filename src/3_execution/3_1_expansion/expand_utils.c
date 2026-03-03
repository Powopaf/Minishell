/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:24:01 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/03 10:32:42 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src/3_execution/3_1_expansion/expand.h"

int	is_dquoted(char *s, size_t pos)
{
	size_t	i;
	size_t	dquote;
	size_t	squote;

	squote = 0;
	dquote = 0;
	i = 0;
	if (!s)
		return (0);
	while (i < pos)
	{
		if (s[i] == '\"' && !squote && !is_backslashed(s, i))
			dquote = !dquote;
		else if (s[i] == '\'' && !dquote && !is_backslashed(s, i))
			squote = !squote;
		i++;
	}
	return (dquote);
}

int	is_squoted(char *s, size_t pos)
{
	size_t	i;
	size_t	dquote;
	size_t	squote;

	squote = 0;
	dquote = 0;
	i = 0;
	if (!s)
		return (0);
	while (i < pos)
	{
		if (s[i] == '\"' && !squote && !is_backslashed(s, i))
			dquote = !dquote;
		else if (s[i] == '\'' && !dquote && !is_backslashed(s, i))
			squote = !squote;
		i++;
	}
	return (squote);
}

int	is_backslashed(char *s, size_t pos)
{
	size_t	i;
	size_t	backs;

	if (!s)
		return (0);
	if (!pos)
		return (0);
	if (s[0] == '\\')
		backs = 1;
	else
		backs = 0;
	i = 1;
	while (i < pos)
	{
		if (s[i] == '\\')
			backs = !backs;
		else if (s[i] != '\\')
			backs = 0;
		i++;
	}
	return (backs);
}
