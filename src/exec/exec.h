/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:08:20 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/05 23:08:22 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../../struct.h"

/**
 * Executes the AST starting at the root node.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - AST root node.
 * @returns {int} Exit status of the executed pipeline.
 */
int	exec_root(t_shell *sh, t_ast *node);

#endif
