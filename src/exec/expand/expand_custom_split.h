/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_custom_split.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:19:05 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/25 14:03:45 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_CUSTOM_SPLIT_H
# define EXPAND_CUSTOM_SPLIT_H

# include "../../../libft/libft.h"
# include <stdlib.h>
# include "expand.h"

/**
 * @brief Custom split using ' ', '\t' and '\n' as delimiters.
 * @param s - string to split
 * @return char** - array of splitted strings
 */
char	**split(char *s);

/**
 * @brief Custom split using ' ', '\t' and '\n' as delimiters every arg of an
 * AST node.
 * @param sh - shell context.
 * @param node - node whose args to be splitted.
 */
void	split_args(t_shell *sh, t_ast *node);

#endif
