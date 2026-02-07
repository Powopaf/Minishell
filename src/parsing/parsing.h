/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:01:47 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/05 23:01:48 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../struct.h"
/**
 * Builds an AST from the token list.
 * @param {t_shell *} sh - Shell context.
 * @param {t_token **} tokens - Pointer to token list.
 * @returns {t_ast*} Root of the AST or NULL on failure.
 */
t_ast	*parser(t_shell *sh, t_token **tokens);

#endif
