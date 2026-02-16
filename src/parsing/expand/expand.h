/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:03:22 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/15 12:39:45 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../../../struct.h"
# include "../../../libft/libft.h"
# include "../../error/err.h"
# include <dirent.h>
# include <stdlib.h>
# include <sys/types.h>


void	expand(t_shell *sh, t_ast *current_node);

/**
 * Expands variables in the AST node arguments.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} current_node - AST node to expand.
 */
void	expand_var(t_shell *sh, t_ast *current_node);

void	expand_wildcards(t_shell *sh, t_ast *current_node);

#endif
