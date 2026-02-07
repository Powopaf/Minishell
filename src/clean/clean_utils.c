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
#include <stdlib.h>
#include <unistd.h>

void	clean_redir(t_redir	*redir)
{
	if (!redir)
		return ;
	// TODO: check if we can remove the if
	if (redir->file)
		free(redir->file);
	if (redir->eofkw)
		free(redir->eofkw);
	close(redir->fd_in);
	close(redir->fd_out);
	free(redir);
}

void	redir_clear(t_redir **redir, void (*del)(t_redir *))
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

void	tokens_clear(t_token **token, void (*del)(t_token *))
{
	t_token	*current;
	t_token	*tokenfree;

	if (!token || !*token)
		return ;
	current = *token;
	while (current)
	{
		tokenfree = current;
		current = current->next;
		del(tokenfree);
		free(tokenfree);
	}
	*token = NULL;
}
