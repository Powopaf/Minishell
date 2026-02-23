/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:30:03 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/21 14:38:45 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "../error/err.h"
#include "../../libft/libft.h"

static int	add_arg(t_shell *sh, t_ast *node, char *arg)
{
	char	**tmp;

	if (!arg)
		return (1);
	tmp = ft_add_str_array(node->args, arg);
	node->args = tmp;
	if (!node->args)
	{
		error(sh, "malloc", MALLOC_ERR, -FAIL);
		return (0);
	}
	return (1);
}

int	parse_command_args(t_shell *sh, t_ast *node, t_token **tokens)
{
	while (*tokens && (*tokens)->kw == WORD)
	{
		if (!add_arg(sh, node, (*tokens)->token))
			return (0);
		(*tokens) = (*tokens)->next;
	}
	return (1);
}
