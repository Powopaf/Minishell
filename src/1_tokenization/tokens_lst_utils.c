/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:05:00 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/25 10:38:03 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_utils.h"
#include "../error/err.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static void	token_add_back(t_token **token, t_token *new)
{
	t_token	*current;

	if (!new)
		return ;
	new->next = NULL;
	if (!*token)
	{
		*token = new;
		new->prev = NULL;
		return ;
	}
	current = *token;
	while (current->next)
		current = current->next;
	new->prev = current;
	current->next = new;
}

static t_token	*create_token(t_shell *sh, char *token_str, t_token_kw token_kw)
{
	t_token	*token_struct;

	token_struct = malloc(sizeof(t_token));
	if (!token_struct)
	{
		error(sh, "malloc", strerror(errno), -FAIL);
		return (NULL);
	}
	token_struct->token = NULL;
	if (token_str)
	{
		token_struct->token = ft_strdup(token_str);
		if (!token_struct->token)
		{
			free(token_struct);
			error(sh, "malloc", strerror(errno), -FAIL);
			return (NULL);
		}
	}
	token_struct->kw = token_kw;
	return (token_struct);
}

int	add_token(t_shell *sh, char *token, t_token_kw kw)
{
	t_token	*new_tk;

	new_tk = create_token(sh, token, kw);
	if (!new_tk)
		return (0);
	token_add_back(&sh->tokens, new_tk);
	return (1);
}
