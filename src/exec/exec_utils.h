/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paf <paf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:09:07 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/25 13:58:54 by paf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# include "../../struct.h"
# include "../../redir.h"

/**
 * Executes a command node (builtins or external).
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - AST command node.
 * @returns {int} Exit status.
 */
void	exec_cmd(t_shell *sh, t_ast *node);

/**
 * Forks the current process with error handling.
 * @param {t_shell *} sh - Shell context.
 * @returns {pid_t} Child PID or -1 on failure.
 */
pid_t	try_fork(t_shell *sh);

/**
 * Applies redirections for a command.
 * @param {t_shell *} sh - Shell context.
 * @param {t_redir *} redir - Redirection list.
 * @returns {int} EXIT_SUCCESS or EXIT_FAILURE.
 */
int		redir(t_shell *sh, t_redir *redir);

/**
 * Waits for all processes in the AST and returns status.
 * @param {t_ast *} node - AST root node.
 * @returns {int} Final exit status.
 */
int		wait_ast(t_ast *node);

/**
 * Sets up a pipe between AST nodes.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - AST pipe node.
 * @returns {int} EXIT_SUCCESS or EXIT_FAILURE.
 */
int		setup_pipe(t_shell *sh, t_ast *node);

/**
 * Checks whether a path points to a directory.
 * @param {char *} path - Path to check.
 * @returns {int} 1 if directory, otherwise 0.
 */
int		is_dir(char *path);

void	clean_exit_forked_cmd(t_ast *node, char *cmd, char **args, char **envp);

#endif
