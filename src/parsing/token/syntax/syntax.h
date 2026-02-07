/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:04:47 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/05 23:04:53 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "../../../../struct.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

/**
 * Validates the token list syntax.
 * @param {t_shell *} sh - Shell context.
 * @returns {int} EXIT_SUCCESS or EXIT_FAILURE.
 */
int	check_syntax(t_shell *sh);

#endif
