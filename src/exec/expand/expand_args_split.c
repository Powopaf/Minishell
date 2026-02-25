/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:37:42 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/25 14:03:21 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "expand_custom_split.h"

void	split_args(t_shell *sh, t_ast *node)
{
	size_t	i;
	char	**splitted;
	char	**new_args;

	if (!node || !node->args)
		return ;
	new_args = NULL;
	i = 0;
	while (node->args[i])
	{
		splitted = split(node->args[i]);
		if (!splitted)
			;
		else if (!*splitted)
			free(splitted);
		else
		{
			ft_add_arr_arr(&new_args, splitted);
			if (!new_args)
				return (error(sh, "malloc", strerror(errno), -FAIL));
		}
		i++;
	}
	ft_empty_array_strs(node->args);
	node->args = new_args;
}
