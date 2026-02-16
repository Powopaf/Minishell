/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:03:31 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/05 23:03:33 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_UTILS_H
# define EXPAND_UTILS_H

# include "../../../struct.h"

/**
 * Retrieves an environment variable value from the shell context.
 * @param {t_shell *} sh - Shell context.
 * @param {char *} var_name - Variable name to look up.
 * @returns {char*} Newly allocated value or NULL if not found.
 */
char	*collect_env_var(t_shell *sh, char *var_name);

#endif
