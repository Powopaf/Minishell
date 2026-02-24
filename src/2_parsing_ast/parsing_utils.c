/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 07:41:02 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/24 07:43:51 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_logop(t_token *token)
{
	if (token && (token->kw == AND || token->kw == OR
			|| token->kw == SEMICOLON))
		return (1);
	return (0);
}
