/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:10:21 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/05 23:04:23 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "../../../redir.h"
#include "../../error/err.h"
#include "../../../libft/libft.h"
#include "expand_utils.h"
#include <stddef.h>
#include <stdlib.h>

static char	*expand_status(t_shell *sh, char *expand, size_t *i)
{
	char	*exit;
	char	*s;

	if (!expand)
		return (NULL);
	exit = ft_itoa(sh->status);
	if (!exit)
	{
		error(sh, "malloc", MALLOC_ERR, -FAIL);
		return (NULL);
	}
	s = ft_strjoin(expand, exit);
	if (!s)
	{
		error(sh, "malloc", MALLOC_ERR, -FAIL);
		return (NULL);
	}
	free(exit);
	if (!expand)
		free(expand);
	(*i)++;
	return (s);
}

static char	*expand_env_var(t_shell *sh, char *s, char *expand, size_t *i)
{
	int		start;
	char	*var_name;
	char	*var;

	start = ++(*i);
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	var_name = ft_substr(s, start, (*i) - start);
	if (!var_name)
	{
		error(sh, "malloc", MALLOC_ERR, -FAIL);
		return (NULL);
	}
	var = collect_env_var(sh, var_name);
	free(var_name);
	expand = ft_strjoin(expand, var);
	if (var)
		free(var);
	(*i)--;
	return (expand);
}

static char	*expand_str(t_shell *sh, char *s)
{
	char	*expand;
	size_t	i;

	expand = ft_strdup("");
	if (!expand)
	{
		error(sh, "malloc", MALLOC_ERR, -FAIL);
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
			expand = expand_status(sh, expand, &i);
		else if (s[i] == '$' && (ft_isalnum(s[i + 1]) || s[i + 1] == '_'))
			expand = expand_env_var(sh, s, expand, &i);
		else
			expand = ft_strjoin_char(expand, s[i], 1, 1);
		i++;
	}
	return (expand);
}

static void	expand_redirs(t_shell *sh, t_redir *redir)
{
	char	*expand;

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
		}
		redir = redir->next;
	}
}

void	expand_var(t_shell *sh, t_ast *current_node)
{
	size_t	i;
	char	*tmp;

	if (!current_node)
		return ;
	if (current_node->astkw == AST_CMD && current_node->args)
	{
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
	}
	if (current_node->redir)
		expand_redirs(sh, current_node->redir);
	expand_var(sh, current_node->left);
	expand_var(sh, current_node->right);
}
