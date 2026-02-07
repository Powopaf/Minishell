/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:36:01 by flomulle          #+#    #+#             */
/*   Updated: 2025/11/12 18:38:16 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_ilength(long n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	len;
	long	temp;

	temp = n;
	len = ft_ilength(temp);
	if (n < 0)
		temp = -temp;
	s = (char *)malloc((len + 1) * sizeof(*s));
	if (!s)
		return (NULL);
	s[len] = '\0';
	while (len > 0 && temp > 0)
	{
		s[--len] = temp % 10 + '0';
		temp /= 10;
	}
	if (n < 0)
		s[0] = '-';
	if (n == 0)
		s[0] = '0';
	return (s);
}
