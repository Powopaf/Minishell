/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:40:21 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/17 13:10:25 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	compare(char *base, char *s, int squote, int dquote)
{
	if (!*base && !*s)
		return (1);
	if (*base == '\'' && !dquote)
		return (compare(base + 1, s, !squote, dquote));
	if (*base == '\"' && !squote)
		return (compare(base + 1, s, squote, !dquote));
	if (*base == '*' && !squote && !dquote)
	{
		return ((*base && compare(base + 1, s, squote, dquote)) || (*s
				&& compare(base, s + 1, squote, dquote)));
	}
	if (*base == *s)
		return (compare(base + 1, s + 1, squote, dquote));
	return (0);
}

static int	check_match(char ***files, char *s, char *entry, size_t *count)
{
	if (entry[0] != '.' && compare(s, entry, 0, 0))
	{
		if (!ft_addstr_arr(files, entry))
			return (0);
		(*count)++;
	}
	return (1);
}

static char	**expand_wildcards_str(t_shell *sh, char *s, size_t *count)
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
		if (!check_match(&files, s, entry->d_name, count))
			return (error(sh, "malloc", MALLOC_ERR, -FAIL), files);
		entry = readdir(dir);
	}
	closedir(dir);
	if (!(*count))
		ft_addstr_arr(&files, s);
	return (files);
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

int	expand_wildcard_redir_file(t_shell *sh, t_redir *current_redir)
{
	size_t	count;
	char	**tmp;

	if (include_wildcard(current_redir->file))
	{
		tmp = expand_wildcards_str(sh, current_redir->file, &count);
		if (count > 1)
			return (error(sh, current_redir->file, AMB_REDIR, -FAIL),
				ft_empty_array_strs(tmp), 0);
		else
		{
			free(current_redir->file);
			current_redir->file = ft_strdup(*tmp);
			ft_empty_array_strs(tmp);
		}
	}
	return (1);
}
