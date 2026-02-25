/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:09:24 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/25 14:04:36 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_utils.h"

int	isshspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	isshbreak(char c)
{
	if (c == '\n')
		return (1);
	return (0);
}

int	isshellkw(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == ';')
		return (1);
	return (0);
}
