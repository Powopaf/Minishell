/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:41:45 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/26 00:09:45 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_free_param(char **s1, char **s2, int param)
{
	if (!param)
		return ;
	if (s1 && s2 && *s1 == *s2)
	{
		free(*s1);
		*s1 = NULL;
		*s2 = NULL;
		return ;
	}
	if ((param == 1 || param == 3) && s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if ((param == 2 || param == 3) && s2 && *s2)
	{
		free(*s2);
		*s2 = NULL;
	}
}

static void	ft_copy(char **s1, char **s2, char *p)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s1 && *s1)
	{
		while ((*s1)[i])
		{
			p[i] = (*s1)[i];
			i++;
		}
	}
	j = 0;
	if (s2 && *s2)
	{
		while ((*s2)[j])
		{
			p[i] = (*s2)[j];
			i++;
			j++;
		}
	}
	p[i] = '\0';
}

char	*ft_strjoin_free(char **s1, char **s2, int param)
{
	size_t	slen;
	char	*p;

	if ((!s1 || !*s1) && (!s2 || !*s2))
	{
		ft_free_param(s1, s2, param);
		return (NULL);
	}
	slen = 0;
	if (s1 && *s1)
		slen += ft_strlen(*s1);
	if (s2 && *s2)
		slen += ft_strlen(*s2);
	p = (char *)malloc((slen + 1) * sizeof(char));
	if (!p)
	{
		ft_free_param(s1, s2, param);
		return (NULL);
	}
	ft_copy(s1, s2, p);
	ft_free_param(s1, s2, param);
	return (p);
}
