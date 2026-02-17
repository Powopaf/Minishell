/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:20:44 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/17 09:30:29 by flomulle         ###   ########.fr       */
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
