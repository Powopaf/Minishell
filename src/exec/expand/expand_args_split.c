/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:37:42 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/19 12:26:59 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "expand_custom_split.h"

void	split_args(t_shell *sh, t_ast *node)
{
	size_t	i;
	char	**splitted;
	char	**new_args;

	if (!node || !node->args || !*node->args)
		return ;
	new_args = NULL;
	i = 0;
	while (node->args[i])
	{
		splitted = split(node->args[i]);
		if (!splitted)
			return (ft_empty_array_strs(new_args), error(sh, "malloc",
					MALLOC_ERR, -FAIL));
		ft_add_arr_arr(&new_args, splitted);
		if (!new_args)
			return (ft_empty_array_strs(new_args), error(sh, "malloc",
					MALLOC_ERR, -FAIL));
		i++;
	}
	ft_empty_array_strs(node->args);
	node->args = new_args;
}
