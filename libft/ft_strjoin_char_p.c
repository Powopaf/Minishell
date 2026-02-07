/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:20:11 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/14 17:33:45 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_free_param(char **s, int param)
{
	if (!param)
		return ;
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

char	*ft_strjoin_char_p(char **s, char c, int position, int param)
{
	char	*p;
	size_t	i;
	size_t	len;

	if (!s || !*s)
		return (NULL);
	len = ft_strlen(*s);
	p = (char *)malloc((len + 2) * sizeof(char));
	if (!p)
	{
		ft_free_param(s, param);
		return (NULL);
	}
	i = 0;
	if (!position)
		p[i++] = c;
	ft_memcpy(p + i, *s, len);
	i += len;
	if (position)
		p[i++] = c;
	ft_free_param(s, param);
	p[i] = '\0';
	return (p);
}
