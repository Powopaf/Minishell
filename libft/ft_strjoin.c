/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:06:40 by flomulle          #+#    #+#             */
/*   Updated: 2025/11/14 17:03:10 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	slen;
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	slen = 0;
	if (s1)
		slen += ft_strlen(s1);
	if (s2)
		slen += ft_strlen(s2);
	p = (char *)malloc((slen + 1) * sizeof(char));
	if (!p)
		return (NULL);
	if (s1)
	{
		while (*s1)
			*p++ = *s1++;
	}
	if (s2)
	{
		while (*s2)
			*p++ = *s2++;
	}
	*p = '\0';
	return (p - slen);
}
