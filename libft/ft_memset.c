/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:19:29 by flomulle          #+#    #+#             */
/*   Updated: 2025/11/13 10:50:41 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	byte;
	size_t			i;

	p = (unsigned char *)(s);
	byte = (unsigned char)(c);
	i = 0;
	while (i < n)
	{
		p[i] = byte;
		i++;
	}
	return (s);
}
