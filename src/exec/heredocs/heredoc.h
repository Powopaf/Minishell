/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:18:30 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/17 13:20:31 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define PROMPT_HD "> "
# define HEREDOC "/tmp/minishell_heredoc"

# include "../../../struct.h"
# include "../../../redir.h"

/**
 * Check all nodes to collect sequentially heredocs
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - if node is a command, then check if there is a
 * heredoc redir entry to collect.
 */
void	handle_heredocs(t_shell *sh, t_ast *current_node);

#endif
