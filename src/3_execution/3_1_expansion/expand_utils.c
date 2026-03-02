/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:24:01 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/02 00:18:13 by flomulle         ###   ########.fr       */
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
		if (s[i] == '\"' && !squote)
			dquote = !dquote;
		else if (s[i] == '\'' && !dquote)
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
		if (s[i] == '\"' && !squote)
			dquote = !dquote;
		else if (s[i] == '\'' && !dquote)
			squote = !squote;
		i++;
	}
	return (squote);
}
