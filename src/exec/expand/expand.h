/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:03:22 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/17 11:09:19 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../../../libft/libft.h"
# include "../../../redir.h"
# include "../../../struct.h"
# include "../../error/err.h"
# include <dirent.h>
# include <stdlib.h>
# include <sys/types.h>

// expand_var

static void	expand_redirs(t_shell *sh, t_redir *redir);
char		*expand_str(t_shell *sh, char *s);

/**
 * Expands variables in the AST node arguments.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} current_node - AST node to expand.
 */
int			expand_cmd(t_shell *sh, t_ast *current_node);

// expand_wildcards.c
void		expand_wildcards_arg(t_shell *sh, t_ast *current_node);
int			expand_wildcard_redir_file(t_shell *sh, t_redir *current_redir);

// expand_env.c
/**
 * Retrieves an environment variable value from the shell context.
 * @param {t_shell *} sh - Shell context.
 * @param {char *} var_name - Variable name to look up.
 * @returns {char*} Newly allocated value or NULL if not found.
 */
char		*collect_env_var(t_shell *sh, char *var_name);

// expand_utils.c
int			arr_rm_quotes(char ***arr);
char		*strdup_rm_quotes(char *s);

// expand_wildcards_utils.c
int			include_wildcard(char *s);

#endif
