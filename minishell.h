/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:13:03 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/05 11:26:04 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*
========= MACROS ===============================================================
*/

# define MISUSE 2
# define PRG_ERR 666
# define SIG_BASE 128

# define ISDIR "Is a directory"
# define DEBUG "PROGRAM ERROR"

# define PROMPT "minishell> "
# define PROMPT_HD "> "

# define HEREDOC "/tmp/minishell_heredoc"

/*
========= GLOBAL VARIABLE ======================================================
*/

//int			g_signal = 0;

/*
========= STRUCTURES============================================================
*/

typedef struct s_redir
{
	t_token_kw		kw;
	char			*file;
	char			*eofkw;
	int				fd_in;
	int				fd_out;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

#endif
