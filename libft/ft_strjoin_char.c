/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:20:11 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/12 16:38:01 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin_char(char *s, char c, int position, int param)
{
	char	*p;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	p = (char *)malloc((len + 2) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	if (!position)
		p[i++] = c;
	ft_memcpy(p + i, s, len);
	i += len;
	if (position)
		p[i++] = c;
	p[i] = '\0';
	if (param)
		free(s);
	return (p);
}
