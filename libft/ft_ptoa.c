/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:10:05 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/28 11:10:31 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_hex_digit_count(unsigned long n)
{
	int	count;

	count = 1;
	while (n >= 16)
	{
		n /= 16;
		count++;
	}
	return (count);
}

static void	ft_fill_hex_str(char *str, unsigned long n, int digits)
{
	const char	*hex_digits = "0123456789abcdef";

	str[digits] = '\0';
	while (digits > 0)
	{
		str[--digits] = hex_digits[n % 16];
		n /= 16;
	}
}

char	*ft_ptoa(void *ptr)
{
	char			*result;
	unsigned long	addr;
	int				digit_count;

	if (!ptr)
		return (NULL);
	addr = (unsigned long)ptr;
	digit_count = ft_hex_digit_count(addr);
	result = malloc(digit_count + 1);
	if (!result)
		return (NULL);
	ft_fill_hex_str(result, addr, digit_count);
	return (result);
}
