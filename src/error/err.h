/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:06:39 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/15 18:33:29 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include "../../struct.h"

# define SUCCESS 0
# define FAIL 1
# define MALLOC_ERR "Memory allocation failed"
# define MALLOC_FULL_ERR "minishell: malloc: Memory allocation failed"
# define QUOTE_ERR "expected end-quote"
# define PARENTH_ERR "missing a parenthesis"
# define PIPE_ERR "piping wrong"
# define AMB_REDIR "ambiguous redirect"
# define PROMPT_MES "minishell: " // TODO: shoulb equlal to argv[0]
# define CMD_NOT_FND 127
# define CMD_PERM_DND 126
# define MISUSE 2
# define PRG_ERR 666
# define ISDIR "Is a directory"
# define SIG_BASE 128
# define DEBUG "PROGRAM ERROR"
# define WARNING "warning: "

/**
 * Reports a syntax error and updates shell status.
 * @param {t_shell *} sh - Shell context.
 * @param {t_token_kw} kw - Token that caused the syntax error.
 * @param {int} exitno - Exit status to set.
 */
void	syntax_error(t_shell *sh, t_token_kw kw, int exitno);

/**
 * Reports an error with context and updates shell status.
 * @param {t_shell *} shell - Shell context.
 * @param {char *} context - Error context (command or component).
 * @param {char *} why - Error description.
 * @param {int} exitno - Exit status to set.
 */
void	error(t_shell *shell, char *context, char *why, int exitno);

/**
 * @brief Prints a warning when ctrl D is used to close an here_doc,
 * precising the line number.
 * @param sh
 */
void	warning_hd(t_shell *sh);

#endif
