/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:09:24 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/19 11:30:16 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_utils.h"

// ' & "

int	isshspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	isshbreak(char c)
{
	if (c == '\n' || c == '\\')
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
