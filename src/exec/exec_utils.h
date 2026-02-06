/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:09:07 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/06 15:53:06 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
# define PROMPT_HD "> "
# define HEREDOC "/tmp/minishell_heredoc"

#include "../../struct.h"
#include "../../redir.h"

int		exec_cmd(t_shell *sh, t_ast *node);
pid_t	try_fork(t_shell *sh);
int		redir(t_shell *sh, t_redir *redir);
int		wait_ast(t_ast *node);
int		setup_pipe(t_shell *sh, t_ast *node);
int	heredoc(t_shell *sh, t_redir *redir);

#endif
