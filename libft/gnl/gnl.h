/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:39:32 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/12 16:39:36 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# define BUFFER_SIZE 4096
# define FD_MAX 16

# include "stdlib.h"

/**
 * Computes the length of a string.
 * @param {const char*} s - Null-terminated string.
 * @returns {size_t} Number of characters before '\0'.
 */
size_t	strlen_gnl(const char *s);

/**
 * Searches for a character in a string.
 * @param {const char*} s - String to search.
 * @param {int} c - Character to locate.
 * @returns {char*} Pointer to match or NULL.
 */
char	*strchr_gnl(const char *s, int c);

/**
 * Joins two strings into a new allocated string.
 * @param {char*} s1 - First string.
 * @param {char*} s2 - Second string.
 * @returns {char*} Joined string or NULL on failure.
 */
char	*strjoin_gnl(char *s1, char *s2);

/**
 * Copies two strings into a destination buffer.
 * @param {char*} res - Destination buffer.
 * @param {char*} s1 - First string.
 * @param {char*} s2 - Second string.
 */
void	cpy_gnl(char *res, char *s1, char *s2);

#endif
