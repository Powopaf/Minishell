/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:50:55 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/23 13:54:19 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

int	is_redir(t_token *token)
{
	if (!token)
		return (0);
	if (token->kw == REDIR_IN || token->kw == REDIR_HD
		|| token->kw == REDIR_OUT ||token->kw == REDIR_APP)
		return (1);
	return (0);
}
