/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array_strs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:22:43 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/14 17:58:15 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_array_strs(char ***s)
{
	size_t	i;

	if (!s || !*s)
		return ;
	i = 0;
	while ((*s)[i])
	{
		free((*s)[i]);
		(*s)[i] = NULL;
		i++;
	}
	free(*s);
	*s = NULL;
}
