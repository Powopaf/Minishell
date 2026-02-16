/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:40:21 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/15 18:34:54 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "../../../redir.h"

int	compare(char *base, char *s)
{
	if (!*base && !*s)
		return (1);
	if (*base == '*')
		return (compare(base + 1, s) || (*s && compare(base, s + 1)));
	if (*s && *base == *s)
		return (compare(base + 1, s + 1));
	return (0);
}

char	**expand_wildcards_str(t_shell *sh, char *s, size_t *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;

	*count = 0;
	files = malloc(sizeof(char *));
	if (!files)
		return (NULL);
	files[0] = NULL;
	dir = opendir(".");
	if (!dir)
		return (files);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && compare(s, entry->d_name))
		{
			if (!ft_addstr_arr(&files, entry->d_name))
				return (error(sh, "malloc", MALLOC_ERR, -FAIL), files);
			(*count)++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (files);
}

int	include_wildcard(char *s)
{
	size_t	i;
	size_t	squotes;
	size_t	dquotes;

	i = 0;
	squotes = 0;
	dquotes = 0;
	while (s && s[i])
	{
		if (s[i] == '\'')
			squotes++;
		else if (s[i] == '"')
			dquotes++;
		else if (s[i] == '*' && squotes % 2 == 0 && dquotes % 2 == 0)
			return (1);
		i++;
	}
	return (0);
}

void	expand_wildcards_arg(t_shell *sh, t_ast *current_node)
{
	size_t	i;
	char	**new_args;
	size_t	count;
	char	**tmp;

	i = 0;
	new_args = NULL;
	while (current_node->args[i])
	{
		if (!include_wildcard(current_node->args[i]))
			ft_addstr_arr(&new_args, current_node->args[i]);
		else
		{
			tmp = expand_wildcards_str(sh, current_node->args[i], &count);
			ft_add_arr_arr(&new_args, tmp);
		}
		i++;
	}
	ft_empty_array_strs(current_node->args);
	if (new_args)
		current_node->args = new_args;
}

void	expand_wildcard_redir_file(t_shell *sh, t_ast *current_node)
{
	size_t	count;
	char	**tmp;
	t_redir	*current_redir;

	current_redir = current_node->redir;
	while (current_redir)
	{
		if (include_wildcard(current_redir->file))
		{
			tmp = expand_wildcards_str(sh, current_redir->file, &count);
			if (count > 1)
			{
				error(sh, current_redir->file, AMB_REDIR, -FAIL);
				//delete_redir(current_redir);
				continue ;
			}
			else
			{
				free(current_redir->file);
				current_redir->file = ft_strdup(*tmp);
				ft_empty_array_strs(tmp);
			}
		}
		current_redir = current_redir->next;
	}
}

void	expand_wildcards(t_shell *sh, t_ast *current_node)
{
	if (!current_node)
		return ;
	if (current_node->astkw == AST_CMD && current_node->args)
		expand_wildcards_arg(sh, current_node);
	if (current_node->redir)
	{
		expand_wildcard_redir_file(sh, current_node);
	}
	expand_wildcards(sh, current_node->left);
	expand_wildcards(sh, current_node->right);
}
