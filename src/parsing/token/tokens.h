/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:05:35 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/05 23:05:42 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

#include "../../../struct.h"

#define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

int	tokenization(t_shell *sh);
char	*ft_token_to_char(t_token_kw kw);

#endif
