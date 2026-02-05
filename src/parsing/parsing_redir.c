/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:57:30 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/05 23:02:24 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "../error/err.h"
#include "../../redir.h"
#include <stdlib.h>

static void	rediradd_back(t_redir **redir, t_redir *newredir)
{
	t_redir	*current;

	if (!newredir)
		return ;
	if (!*redir)
	{
		*redir = newredir;
		newredir->prev = NULL;
		return ;
	}
	current = *redir;
	while (current->next)
		current = current->next;
	current->next = newredir;
	newredir->prev = current;
}

static t_redir	*create_redir(t_shell *sh, t_token_kw kw, char *file)
{
	t_redir	*redir_struct;

	redir_struct = (t_redir*)malloc(sizeof(t_redir));
	if (!redir_struct)
		return (error(sh, "malloc", MALLOC_ERR, -FAIL), NULL);
	redir_struct->kw = kw;
	redir_struct->file = ft_strdup(file);
	if (!redir_struct->file)
	{
		free(redir_struct);
		error(sh, "malloc", MALLOC_ERR, -FAIL);
		return (NULL);
	}
	redir_struct->eofkw = NULL;
	if (redir_struct->kw == REDIR_HD)
	{
		redir_struct->eofkw = redir_struct->file;
		redir_struct->file = NULL;
	}
	redir_struct->fd_in = -1;
	redir_struct->fd_out = -1;
	redir_struct->prev = NULL;
	redir_struct->next = NULL;
	return (redir_struct);
}

static int	add_redir(t_shell *sh, t_ast *ast_node, t_token_kw kw, char *file)
{
	t_redir	*new_redir;

	new_redir = create_redir(sh, kw, file);
	if (!new_redir)
		return (EXIT_FAILURE);
	rediradd_back(&ast_node->redir, new_redir);
	return (EXIT_SUCCESS);
}

int	parse_redir(t_shell *sh, t_ast *ast_node, t_token **token)
{
	char	*file;

	if (!token || !*token || !ast_node)
		return (EXIT_FAILURE);
	file = NULL;
	while ((*token)->kw >= REDIR_IN && (*token)->kw <= REDIR_APP)
	{
		file = ft_strdup((*token)->next->token);
		if (!file)
		{
			error(sh, "malloc", MALLOC_ERR, -FAIL);
			return (EXIT_FAILURE);
		}
		if (add_redir(sh, ast_node, (*token)->kw, file))
		{
			free(file);
			return (EXIT_FAILURE);
		}
		free(file);
		(*token) = (*token)->next->next;
	}
	return (EXIT_SUCCESS);
}
