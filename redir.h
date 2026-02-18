/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:19:35 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/18 15:15:27 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "struct.h"

typedef struct s_redir
{
	t_token_kw		kw;
	char			*file;
	char			*eofkw;
	int				quoted;
	int				fd_in;
	int				fd_out;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

#endif
