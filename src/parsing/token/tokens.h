/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:05:35 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/12 16:31:40 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "../../../struct.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

/**
 * Tokenizes the current input line into a token list.
 * @param {t_shell *} sh - Shell context.
 * @returns {int} EXIT_SUCCESS or EXIT_FAILURE.
 */
int		tokenization(t_shell *sh);

/**
 * Converts a token kind to its string representation.
 * @param {t_token_kw} kw - Token kind.
 * @returns {char*} Static string representation.
 */
char	*ft_token_to_char(t_token_kw kw);

#endif
