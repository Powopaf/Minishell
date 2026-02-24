/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:45:07 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/24 12:27:49 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

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
	free(expand);
	(*i)++;
	return (s);
}

static char	*expand_env_var(t_shell *sh, char *s, char *expand, size_t *i)
{
	int		start;
	char	*var_name;
	char	*var;
	char	*tmp;

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
	tmp = ft_strjoin(expand, var);
	if (tmp)
		free(expand);
	else
		tmp = expand;
	if (var)
		free(var);
	(*i)--;
	return (tmp);
}

static char	*expand_var(t_shell *sh, char *s, char *expand)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && (!i || s[i - 1] != '\\') && s[i + 1] == '?'
			&& !is_squoted(s, i))
			expand = expand_status(sh, expand, &i);
		else if (s[i] == '$' && (!i || s[i - 1] != '\\') && !is_squoted(s, i)
			&& !is_dquoted (s, i) && (s[i + 1] == '\"' || s[i + 1] == '\''))
			;
		else if (s[i] == '$' && (!i || s[i - 1] != '\\') && (ft_isalnum(s[i
					+ 1]) || s[i + 1] == '_') && !is_squoted(s, i))
			expand = expand_env_var(sh, s, expand, &i);
		else
			expand = ft_strjoin_char(expand, s[i], 1, 1);
		i++;
	}
	return (expand);
}

char	*expand_str(t_shell *sh, char *s)
{
	char	*expand;

	expand = ft_strdup("");
	if (!expand)
		return (error(sh, "malloc", MALLOC_ERR, -FAIL), NULL);
	expand = expand_var(sh, s, expand);
	return (expand);
}
