/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:03:22 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/05 23:03:23 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../../../struct.h"

/**
 * Expands variables in the AST node arguments.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} current_node - AST node to expand.
 */
void	expand_var(t_shell *sh, t_ast *current_node);

#endif
