/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:04:47 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/20 17:21:22 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "../../../../struct.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

/**
 * Open secondary prompt to keep typing
 * @param {t_shell *} sh - Shell context.
 * @returns {int} EXIT_SUCCESS or EXIT_FAILURE.
 */
int	backslash_syntax(t_shell *sh);

/**
 * Validates the token list syntax.
 * @param {t_shell *} sh - Shell context.
 * @returns {int} EXIT_SUCCESS or EXIT_FAILURE.
 */
int	check_syntax(t_shell *sh);

/**
 * Validates the quoting syntax.
 * @param {t_shell *} sh - Shell context.
 * @returns {int} 0 on error, 1 on success.
 */
int	quote_syntax(t_shell *sh);

#endif
