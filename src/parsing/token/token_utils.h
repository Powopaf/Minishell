/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:05:12 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/05 23:05:14 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_UTILS_H
# define TOKENS_UTILS_H

# include "../../../struct.h"

#define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

int	isshspace(char c);
int	isshbreak(char c);
int	isshellkw(char c);
ssize_t	add_key_token(t_shell *sh, ssize_t i);
int	add_token(t_shell *sh, char *token, t_token_kw kw);

#endif
