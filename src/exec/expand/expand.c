/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:10:21 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/17 10:59:49 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../../../redir.h"
#include "../../error/err.h"
#include "expand.h"
#include <stddef.h>
#include <stdlib.h>

static void	expand_redirs_hd(t_shell *sh, t_redir *redir)
{
	char	*expand;
	char	*tmp;

	while (redir)
	{
		if (redir->eofkw)
		{
			expand = expand_str(sh, redir->eofkw);
			if (expand)
			{
				free(redir->eofkw);
				redir->eofkw = expand;
			}
			tmp = strdup_rm_quotes(redir->eofkw);
			if (tmp)
			{
				free(redir->eofkw);
				redir->eofkw = tmp;
			}
		}
		redir = redir->next;
	}
}

static int	expand_redirs_files(t_shell *sh, t_redir *redir)
{
	char	*expand;
	char	*tmp;

	while (redir)
	{
		if (redir->file)
		{
			expand = expand_str(sh, redir->file);
			if (expand)
			{
				free(redir->file);
				redir->file = expand;
			}
			if (!expand_wildcard_redir_file(sh, redir))
				return (0);
			tmp = strdup_rm_quotes(redir->eofkw);
			if (tmp)
			{
				free(redir->eofkw);
				redir->eofkw = tmp;
			}
		}
		redir = redir->next;
	}
	return (1);
}

int	expand_args(t_shell *sh, t_ast *current_node)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (current_node->args[i])
	{
		tmp = expand_str(sh, current_node->args[i]);
		if (tmp)
		{
			free(current_node->args[i]);
			current_node->args[i] = tmp;
		}
		i++;
	}
	expand_wildcards_arg(sh, current_node);
	if (!arr_rm_quotes(&current_node->args))
		return (error(sh, "malloc", MALLOC_ERR, -FAIL), 0);
	return (1);
}

int	expand_cmd(t_shell *sh, t_ast *current_node)
{
	if (current_node && current_node->astkw == AST_CMD)
	{
		if (current_node->args)
			if (!expand_args(sh, current_node))
				return (0);
		if (current_node->redir)
		{
			if (!expand_redirs_files(sh, current_node->redir))
				return (0);
			expand_redirs_hd(sh, current_node->redir);
		}
	}
	return (1);
}
