/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:05:32 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/26 11:06:50 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean_shell.h"
#include <stddef.h>

void	ft_clean_redir(t_redir	*redir)
{
	if (!redir)
		return ;
	ft_free_str(&redir->file);
	ft_free_str(&redir->eofkw);
	ft_close_fd(&redir->fd_in);
	ft_close_fd(&redir->fd_out);
	free(redir);
}

void	ft_redir_clear(t_redir **redir, void (*del)(t_redir *))
{
	t_redir	*current;
	t_redir	*redirfree;

	if (!redir || !*redir)
		return ;
	current = *redir;
	while (current)
	{
		redirfree = current;
		current = current->next;
		del(redirfree);
	}
	*redir = NULL;
}
